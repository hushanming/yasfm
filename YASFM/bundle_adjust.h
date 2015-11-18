/*
* Filip Srajer
* filip.srajer (at) fel.cvut.cz
* Center for Machine Perception
* Czech Technical University in Prague
*
* This software is under construction.
* 05/2015
*/

#pragma once

#include <string>
#include <unordered_set>
#include <vector>

#include "Eigen\Dense"

#include "defines.h"
#include "options.h"
#include "sfm_data.h"

using Eigen::Vector3d;
using Eigen::Vector4d;
using Eigen::Matrix3d;
using Eigen::Matrix4d;
using namespace yasfm;
using std::string;
using std::unordered_set;
using std::vector;

namespace yasfm
{

// Run bundle adjustement on all the cameras and all the points.
YASFM_API void bundleAdjust(const OptionsBundleAdjustment& opt,ptr_vector<Camera> *cams,
  Points *pts);
// Run bundle adjustement on all the cameras and keep the points fixed.
YASFM_API void bundleAdjustCams(const OptionsBundleAdjustment& opt,ptr_vector<Camera> *cams,
  Points *pts);
// Run bundle adjustement on and all the points and keep the cameras fixed.
YASFM_API void bundleAdjustPoints(const OptionsBundleAdjustment& opt,ptr_vector<Camera> *cams,
  Points *pts);

YASFM_API void bundleAdjust(const OptionsBundleAdjustment& opt,const vector<bool>& constantCams,
  const vector<bool>& constantPoints,ptr_vector<Camera> *cams,Points *pts);

YASFM_API void bundleAdjustOneCam(const OptionsBundleAdjustment& opt,int camIdx,Camera *cam,
  Points *pts);

YASFM_API void bundleAdjustOneCam(const OptionsBundleAdjustment& opt,
  int camIdx,const vector<bool>& constantPoints,Camera *cam,Points *pts);

struct SharedParameterGroup
{
  vector<int> camsIdxs;
  vector<vector<int>> paramsIdxs;
};

vector<SharedParameterGroup>;

} // namespace yasfm

namespace
{

} // namespace