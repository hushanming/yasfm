/*
* Filip Srajer
* filip.srajer (at) fel.cvut.cz
* Center for Machine Perception
* Czech Technical University in Prague
*
* This software is under construction.
* 02/2015
*/

#include "ransac.h"

#include <cassert>
#include <iostream>
#include <random>
#include <vector>
#include <unordered_set>

#include "Eigen\Dense"

using Eigen::MatrixXd;
using std::cerr;
using std::endl;
using std::unordered_set;
using std::vector;

namespace yasfm
{

std::default_random_engine generator;

void generateRandomIndices(int numToGenerate,int numOverall,vector<int>& idxs)
{
  assert(numToGenerate <= numOverall);

  if(idxs.size() < numToGenerate)
    idxs.resize(numToGenerate);

  std::uniform_int_distribution<int> distribution(0,numOverall - 1);
  unordered_set<int> generated;
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