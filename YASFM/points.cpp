/*
* Filip Srajer
* filip.srajer (at) fel.cvut.cz
* Center for Machine Perception
* Czech Technical University in Prague
*
* This software is under construction.
* 05/2015
*/

#include "points.h"

#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <unordered_set>
#include <vector>

#include "Eigen\Dense"

#include "utils.h"
#include "options.h"

using Eigen::VectorXd;
using Eigen::Vector3d;
using Eigen::Vector4d;
using Eigen::Matrix3d;
using Eigen::Matrix4d;
using Eigen::MatrixXd;
using namespace yasfm;
using std::list;
using std::string;
using std::vector;
using std::unordered_map;
using std::unordered_set;
using std::queue;
using std::pair;
using std::cout;
using std::endl;
using std::cerr;

namespace yasfm
{

/*void findPointColors(const vector<int>& points2tracks,const vector<bool>& pointsMask,
  const vector<NViewMatch>& tracks,const ptr_vector<ICamera>& cams,
  const unordered_set<int>& addedCams,vector<Vector3uc>& pointsColors)
{
  pointsColors.resize(points2tracks.size(),Vector3uc(0,0,0));
  for(size_t ptIdx = 0; ptIdx < points2tracks.size(); ptIdx++)
  {
    if(!pointsMask.empty() && pointsMask[ptIdx])
    {
      for(const auto& camKey : tracks[points2tracks[ptIdx]])
      {
        if(addedCams.count(camKey.first) > 0)
        {
          pointsColors[ptIdx] = cams[camKey.first]->feature(camKey.second).color();
          break;
        }
      }
    }
  }
}

void findPointColors(const IDataset& dts,vector<Vector3uc>& pointsColors)
{
  findPointColors(dts.points2tracks(),dts.pointsMask(),
    dts.tracks(),dts.cams(),dts.addedCams(),pointsColors);
}*/

void twoViewMatchesToNViewMatches(const ptr_vector<Camera>& cams,
  const pair_umap<CameraPair>& pairs,
  vector<NViewMatch> *nViewMatches)
{
  cout << "Searching for N view matches ... ";
  pair_umap<vector<int>> matches;
  vector<uset<int>> matchedCams;
  convertMatchesToLocalRepresentation(cams,pairs,&matchedCams,&matches);

  vector<vector<bool>> visitedFeats;
  visitedFeats.resize(cams.size());
  for(size_t i = 0; i < cams.size(); i++)
  {
    visitedFeats[i].resize(cams[i]->keys().size(),false);
  }

  int nCams = static_cast<int>(cams.size());
  for(int camIdx = 0; camIdx < nCams; camIdx++)
  {
    int nFeatures = static_cast<int>(cams[camIdx]->keys().size());
    for(int featIdx = 0; featIdx < nFeatures; featIdx++)
    {
      if(!visitedFeats[camIdx][featIdx])
      {
        findNViewMatch(matchedCams,matches,camIdx,featIdx,&visitedFeats,nViewMatches);
      }
    }
  }
  cout << "found " << nViewMatches->size() << "\n";
}

void nViewMatchesToTwoViewMatches(const vector<NViewMatch>& nViewMatches,
  IntPair pair,vector<IntPair> *twoViewMatches,vector<int> *nViewMatchesIdxs)
{
  int camIdxFrom = pair.first;
  int camIdxTo = pair.second;
  int numNView = static_cast<int>(nViewMatches.size());
  for(int iNView = 0; iNView < numNView; iNView++)
  {
    const auto& nViewMatch = nViewMatches[iNView];
    if(nViewMatch.count(camIdxFrom) > 0 && nViewMatch.count(camIdxTo) > 0)
    {
      twoViewMatches->emplace_back(nViewMatch.at(camIdxFrom),nViewMatch.at(camIdxTo));
      nViewMatchesIdxs->push_back(iNView);
    }
  }
}

void reconstructPoints(const IntPair& camsIdxs,const Camera& cam1,const Camera& cam2,
  const vector<int>& nViewMatchIdxs,Points *points)
{
  cout << "Reconstructing " << nViewMatchIdxs.size() << " points\n";
  vector<Vector3d> coord;
  coord.reserve(nViewMatchIdxs.size());
  Matrix34d Rt1 = cam1.pose();
  Matrix34d Rt2 = cam2.pose();
  vector<bool> isInFrontOfBoth(nViewMatchIdxs.size(),true);
  for(size_t i = 0; i < nViewMatchIdxs.size(); i++)
  {
    const auto& nViewMatch = points->matchesToReconstruct()[nViewMatchIdxs[i]];
    Vector2d key1 = cam1.keyNormalized(nViewMatch.at(camsIdxs.first));
    Vector2d key2 = cam2.keyNormalized(nViewMatch.at(camsIdxs.second));

    coord.emplace_back();
    auto& pt = coord.back();
    triangulate(Rt1,Rt2,key1,key2,&pt);

    isInFrontOfBoth[i] = isInFrontNormalizedP(Rt1,pt) && isInFront(Rt2,pt);
  }

  vector<int> nViewMatchIdxsFiltered = nViewMatchIdxs;
  filterVector(isInFrontOfBoth,&nViewMatchIdxsFiltered);
  filterVector(isInFrontOfBoth,&coord);
  points->addPoints(camsIdxs,nViewMatchIdxsFiltered,coord);
}

void reconstructPoints(const ptr_vector<Camera>& cams,
  const vector<SplitNViewMatch>& matchesToReconstruct,Points *points)
{
  cout << "Reconstructing " << matchesToReconstruct.size() << " points\n";
  vector<Matrix34d> Rts(cams.size());
  vector<bool> RtsValid(cams.size(),false);
  vector<Vector3d> ptCoord(matchesToReconstruct.size());
  vector<bool> isInFrontOfAll(ptCoord.size(),true);

  for(size_t iMatch = 0; iMatch < matchesToReconstruct.size(); iMatch++)
  {
    const auto& match = matchesToReconstruct[iMatch];
    vector<Vector2d> keys;
    vector<int> camIdxs;
    keys.reserve(match.observedPart.size());
    camIdxs.reserve(match.observedPart.size());
    for(const auto& camKey : match.observedPart)
    {
      int camIdx = camKey.first;
      camIdxs.push_back(camIdx);
      if(!RtsValid[camIdx])
      {
        Rts[camIdx] = cams[camIdx]->pose();
        RtsValid[camIdx] = true;
      }
      keys.emplace_back(cams[camIdx]->keyNormalized(camKey.second));
    }
    if(match.observedPart.size() == 2)
      triangulate(Rts[camIdxs[0]],Rts[camIdxs[1]],keys[0],keys[1],&ptCoord[iMatch]);
    else
      triangulate(Rts,camIdxs,keys,&ptCoord[iMatch]);

    for(size_t iProj = 0; iProj < camIdxs.size(); iProj++)
    {
      if(!isInFront(Rts[camIdxs[iProj]],ptCoord[iMatch]))
      {
        isInFrontOfAll[iMatch] = false;
        break;
      }
    }
  }

  vector<SplitNViewMatch> matchesToReconstructFiltered = matchesToReconstruct;
  filterVector(isInFrontOfAll,&matchesToReconstructFiltered);
  filterVector(isInFrontOfAll,&ptCoord);
  points->addPoints(ptCoord,matchesToReconstructFiltered);
}

void triangulate(const Matrix34d& P1,const Matrix34d& P2,const vector<Vector2d>& keys1,
  const vector<Vector2d>& keys2,const vector<IntPair>& matches,vector<Vector3d> *ppts)
{
  auto& pts = *ppts;
  pts.resize(matches.size());
  for(size_t i = 0; i < pts.size(); i++)
  {
    triangulate(P1,P2,keys1[matches[i].first],keys2[matches[i].second],&pts[i]);
  }
}

void triangulate(const Matrix34d& P1,const Matrix34d& P2,const Vector2d& key1,
  const Vector2d& key2,Vector3d *pt)
{
  Matrix4d D,S;
  D.row(0) = key1(0) * P1.row(2) - P1.row(0);
  D.row(1) = key1(1) * P1.row(2) - P1.row(1);
  D.row(2) = key2(0) * P2.row(2) - P2.row(0);
  D.row(3) = key2(1) * P2.row(2) - P2.row(1);

  // S for numerical conditioning
  Vector4d maxCols = D.cwiseAbs().colwise().maxCoeff();
  S = maxCols.cwiseInverse().asDiagonal();

  Eigen::JacobiSVD<Matrix4d> svd(D*S,Eigen::ComputeFullV);

  Vector4d ptHom;
  ptHom.noalias() = S*(svd.matrixV().rightCols(1));
  *pt = ptHom.hnormalized();
}

void triangulate(const vector<Matrix34d>& Ps,const vector<int>& PsToUse,
  const vector<Vector2d>& keys,Vector3d *pt)
{
  MatrixXd A;
  VectorXd b;
  A.resize(2 * PsToUse.size(),3);
  b.resize(2 * PsToUse.size());
  for(size_t i = 0; i < PsToUse.size(); i++)
  {
    const auto& P = Ps[PsToUse[i]];
    const auto& key = keys[i];
    A.row(2 * i) = key(0) * P.block(2,0,1,3) - P.block(0,0,1,3);
    A.row(2 * i + 1) = key(1) * P.block(2,0,1,3) - P.block(1,0,1,3);
    b(2 * i) = P(0,3) - key(0) * P(2,3);
    b(2 * i + 1) = P(1,3) - key(1) * P(2,3);
  }

  *pt = A.jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV).solve(b);
}

bool isInFront(const Matrix34d& P,const Vector3d& point)
{
  double projCoord2 = P.row(2).dot(point.homogeneous());
  return (projCoord2*P.leftCols(3).determinant()) > 0.;
}

bool isInFrontNormalizedP(const Matrix34d& P,const Vector3d& point)
{
  double projCoord2 = P.row(2).dot(point.homogeneous());
  return projCoord2 > 0.;
}

void extractCandidateNewPoints(int minObservingCams,double rayAngleThresh,
  const uset<int>& reconstructedCams,const ptr_vector<Camera>& cams,
  vector<NViewMatch> *pnViewMatches,vector<SplitNViewMatch> *pextracted)
{
  auto& matches = *pnViewMatches;
  auto& extracted = *pextracted;
  vector<int> toReconstructIdxs;
  extracted.emplace_back();
  int nMatches = static_cast<int>(matches.size());
  for(int iMatch = 0; iMatch < nMatches; iMatch++)
  {
    auto& curr = extracted.back();
    for(const auto& camKey : matches[iMatch])
    {
      int camIdx = camKey.first;
      if(reconstructedCams.count(camIdx) > 0)
      {
        curr.observedPart.emplace(camIdx,camKey.second);
      } else
      {
        curr.unobservedPart.emplace(camIdx,camKey.second);
      }
    }
    if(curr.observedPart.size() >= minObservingCams &&
      isWellConditioned(rayAngleThresh,cams,curr.observedPart))
    {
      toReconstructIdxs.push_back(iMatch);
      extracted.emplace_back();
    } else
    {
      curr.observedPart.clear();
      curr.unobservedPart.clear();
    }
  }
  extracted.pop_back();
  filterOutOutliers(toReconstructIdxs,&matches);
}

void findCamToSceneMatches(const uset<int>& camsToIgnore,int numCams,
  const Points& points,vector<vector<IntPair>> *pmatches)
{
  auto &matches = *pmatches;
  matches.resize(numCams);
  for(int ptIdx = 0; ptIdx < points.numPts(); ptIdx++)
  {
    for(const auto& camKey : points.ptData()[ptIdx].toReconstruct)
    {
      if(camsToIgnore.count(camKey.first) == 0)
      {
        matches[camKey.first].emplace_back(camKey.second,ptIdx);
      }
    }
  }
}

bool isWellConditioned(double rayAngleThresh,const ptr_vector<Camera>& cams,
  const NViewMatch& pointViews)
{
  auto camKey1 = pointViews.begin();
  for(; camKey1 != pointViews.end(); ++camKey1)
  {
    const auto& cam1 = *cams[camKey1->first];
    auto camKey2 = camKey1;
    ++camKey2;
    for(; camKey2 != pointViews.end(); ++camKey2)
    {
      const auto& cam2 = *cams[camKey2->first];
      double angle = computeRayAngle(cam1,camKey1->second,
        cam2,camKey2->second);
      if(RAD2DEG(angle) > rayAngleThresh)
        return true;
    }
  }
  return false;
}

double computeRayAngle(const Camera& cam1,int key1Idx,
  const Camera& cam2,int key2Idx)
{
  Vector2d key1Norm = cam1.keyNormalized(key1Idx);
  Vector2d key2Norm = cam2.keyNormalized(key2Idx);
  Vector3d ray1 = cam1.R().transpose() * key1Norm.homogeneous();
  Vector3d ray2 = cam2.R().transpose() * key2Norm.homogeneous();
  return acos(ray1.dot(ray2) / (ray1.norm() * ray2.norm()));
}

void removeIllConditionedPoints(double rayAngleThresh,
  const ptr_vector<Camera>& cams,Points *ppts)
{
  auto& pts = *ppts;
  vector<bool> wellConditioned(pts.numPts(),false);
  for(int ptIdx = 0; ptIdx < pts.numPts(); ptIdx++)
  {
    const auto& pt = pts.ptCoord()[ptIdx];
    const auto& views = pts.ptData()[ptIdx].reconstructed;
    auto camKey1 = views.begin();
    for(; camKey1 != views.end() && !wellConditioned[ptIdx]; ++camKey1)
    {
      Vector3d ray1 = pt - cams[camKey1->first]->C();
      ray1.normalize();
      auto camKey2 = camKey1;
      ++camKey2;
      for(; camKey2 != views.end() && !wellConditioned[ptIdx]; ++camKey2)
      {
        Vector3d ray2 = pt - cams[camKey2->first]->C();
        ray2.normalize();
        double angle = RAD2DEG(acos(ray1.dot(ray2)));
        wellConditioned[ptIdx] = angle > rayAngleThresh;
      }
    }
  }
  int numOrig = pts.numPts();
  pts.removePoints(wellConditioned);
  int numRemoved = numOrig - pts.numPts();
  cout << "Removing " << numRemoved << " ill conditioned points\n";
}

/*
void filterIllConditionedTracks(const ptr_vector<ICamera>& cams,double rayAngleThresh,
  list<vector<IntPair>>& tracks,vector<int>& trackIDs)
{
  rayAngleThresh = DEG2RAD(rayAngleThresh);
  vector<Matrix3d> invKs;
  vector<bool> invKComputed;
  invKs.resize(cams.size());
  invKComputed.resize(cams.size(),false);

  auto trackID = trackIDs.begin();
  for(auto track = tracks.begin(); track != tracks.end(); )
  {
    bool illConditioned = true;
    for(size_t i = 0; i < track->size(); i++)
    {
      int cam1 = (*track)[i].first;
      int key1 = (*track)[i].second;
      if(!invKComputed[cam1])
      {
        invKComputed[cam1] = true;
        invKs[cam1] = cams[cam1]->K().inverse();
      }

      Vector3d ray1 = cams[cam1]->R().transpose() * invKs[cam1] * 
        cams[cam1]->feature(key1).coord().homogeneous();

      for(size_t j = i+1; j < track->size(); j++)
      {
        int cam2 = (*track)[j].first;
        int key2 = (*track)[j].second;
        if(!invKComputed[cam2])
        {
          invKComputed[cam2] = true;
          invKs[cam2] = cams[cam2]->K().inverse();
        }

        Vector3d ray2 = cams[cam2]->R().transpose() * invKs[cam2] * 
          cams[cam2]->feature(key2).coord().homogeneous();

        double angle = acos( ray1.dot(ray2) / (ray1.norm() * ray2.norm()) );
        if(angle > rayAngleThresh)
        {
          illConditioned = false;
          j = track->size();
          i = track->size();
        }
      }
    }
    if(illConditioned)
    {
      track = tracks.erase(track);
      trackID = trackIDs.erase(trackID);
    } else
    {
      ++track;
      ++trackID;
    }
  }
}
*/


void removeHighReprojErrorPoints(double avgReprojErrThresh,const ptr_vector<Camera>& cams,
  Points *ppts)
{
  auto& pts = *ppts;
  int nPts = static_cast<int>(pts.ptCoord().size());
  vector<bool> keep(nPts);
  int nToRemove = 0;
  for(int iPt = 0; iPt < nPts; iPt++)
  {
    double err = 0;
    const auto& reconstructPointViews = pts.ptData()[iPt].reconstructed;
    for(const auto& camKey : reconstructPointViews)
    {
      const auto& cam = *cams[camKey.first];
      const auto& key = cam.key(camKey.second);
      Vector2d proj;
      cam.project(pts.ptCoord()[iPt],&proj);
      err += (proj - key).norm();
    }
    err /= reconstructPointViews.size();
    keep[iPt] = err < avgReprojErrThresh;
    nToRemove += !keep[iPt];
  }
  cout << "Removing " << nToRemove << " points with high reprojection error\n";
  pts.removePoints(keep);
}

} // namespace yasfm

namespace
{

void findNViewMatch(const vector<uset<int>>& matchedCams,
  const pair_umap<vector<int>>& matches,int startCamIdx,int startFeatIdx,
  vector<vector<bool>> *pvisitedFeats,vector<NViewMatch> *nViewMatches)
{
  auto& visitedFeats = *pvisitedFeats;
  bool isConsistent = true; // no two different features in the same image
  nViewMatches->emplace_back();
  auto& nViewMatch = nViewMatches->back();

  // the .first symbolizes camIdx and .second respective featIdx
  queue<IntPair> q;

  q.emplace(startCamIdx,startFeatIdx);
  visitedFeats[startCamIdx][startFeatIdx] = true;

  while(!q.empty())
  {
    int cam1 = q.front().first;
    int feat1 = q.front().second;
    q.pop();

    if(isConsistent && (nViewMatch.count(cam1) == 0))
    {
      nViewMatch[cam1] = feat1;
    } else
    {
      isConsistent = false;
    }

    for(int cam2 : matchedCams[cam1])
    {
      int feat2 = matches.at(IntPair(cam1,cam2))[feat1];
      if(feat2 >= 0 && !visitedFeats[cam2][feat2])
      {
        q.emplace(cam2,feat2);
        visitedFeats[cam2][feat2] = true;
      }
    }
  }
  if(!isConsistent || nViewMatch.size() < 2)
  {
    nViewMatches->pop_back();
  }
}

void convertMatchesToLocalRepresentation(const ptr_vector<Camera>& cams,
  const pair_umap<CameraPair>& pairs,vector<uset<int>> *pmatchedCams,
  pair_umap<vector<int>> *pmatches)
{
  auto& matchedCams = *pmatchedCams;
  auto& matches = *pmatches;
  matchedCams.resize(cams.size());
  for(const auto& pair : pairs)
  {
    IntPair idx = pair.first;
    int cam1 = idx.first;
    int cam2 = idx.second;
    IntPair reversedIdx(cam2,cam1);

    matchedCams[cam1].insert(cam2);
    matchedCams[cam2].insert(cam1);
    matches[idx].resize(cams[cam1]->keys().size(),-1);
    matches[reversedIdx].resize(cams[cam2]->keys().size(),-1);

    for(const auto& origMatch : pair.second.matches)
    {
      matches[idx][origMatch.first] = origMatch.second;
      matches[reversedIdx][origMatch.second] = origMatch.first;
    }
  }
}

} // namespace