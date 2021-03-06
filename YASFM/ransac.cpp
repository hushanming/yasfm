#include "ransac.h"

#include <cassert>
#include <random>
#include <unordered_set>

namespace yasfm
{

std::default_random_engine generator;

void generateRandomIndices(int numToGenerate,int numOverall,vector<int> *pidxs)
{
  auto& idxs = *pidxs;

  if(idxs.size() < numToGenerate)
    idxs.resize(numToGenerate);

  std::uniform_int_distribution<int> distribution(0,numOverall - 1);
  std::unordered_set<int> generated;
  generated.reserve(numToGenerate);

  for(int i = 0; i < numToGenerate; i++)
  {
    int idx;
    do
    {
      idx = distribution(generator);
    } while(generated.count(idx) > 0);

    generated.insert(idx);
    idxs[i] = idx;
  }
}

int sufficientNumberOfRounds(int nInliers,int nPoints,int sampleSize,
  double confidence)
{
  if(confidence == 1.)
    return INT_MAX;
  double _nInliers = nInliers;
  double q = 1.;
  for(int i = 0; i < sampleSize; i++)
  {
    q *= static_cast<double>(nInliers - i) / (nPoints - i);
  }
  if(q <= std::numeric_limits<double>::epsilon())
  {
    return INT_MAX;
  } else
  {
    double nRounds = log(1. - confidence) / log(1. - q);
    return static_cast<int>(std::min(nRounds,static_cast<double>(INT_MAX)));
  }
}

double computeInitAvgSamplesDrawnPROSAC(int ransacRounds,int nMatches,int minMatches)
{
  double res = ransacRounds;
  for(int i = 0; i < minMatches; i++)
  {
    res *= static_cast<double>(minMatches - i) / static_cast<double>(nMatches - i);
  }
  return res;
}

double computeNextAvgSamplesDrawnPROSAC(double avgSamplesDrawn,int nUsedMatches,int minMatches)
{
  double res = avgSamplesDrawn;
  res *= static_cast<double>(nUsedMatches + 1) / static_cast<double>(nUsedMatches + 1 - minMatches);
  return res;
}

} // namespace