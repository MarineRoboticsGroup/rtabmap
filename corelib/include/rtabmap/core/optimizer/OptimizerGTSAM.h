/*
Copyright (c) 2010-2016, Mathieu Labbe - IntRoLab - Universite de Sherbrooke
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the Universite de Sherbrooke nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef OPTIMIZERGTSAM_H_
#define OPTIMIZERGTSAM_H_

#ifdef RTABMAP_GTSAM
#include <gtsam/geometry/Pose2.h>
#include <gtsam/geometry/Pose3.h>
#include <gtsam/inference/Key.h>
#include <gtsam/inference/Symbol.h>
#include <gtsam/slam/PriorFactor.h>
#include <gtsam/slam/BetweenFactor.h>
#include <gtsam/sam/BearingRangeFactor.h>
#include <gtsam/sam/RangeFactor.h>
#include <gtsam/nonlinear/NonlinearFactorGraph.h>
#include <gtsam/nonlinear/GaussNewtonOptimizer.h>
#include <gtsam/nonlinear/DoglegOptimizer.h>
#include <gtsam/nonlinear/LevenbergMarquardtOptimizer.h>
#include <gtsam/nonlinear/NonlinearOptimizer.h>
#include <gtsam/nonlinear/Marginals.h>
#include <gtsam/nonlinear/Values.h>
#endif // end RTABMAP_GTSAM

#include "rtabmap/core/RtabmapExp.h" // DLL export/import defines

#include <rtabmap/core/Optimizer.h>

namespace rtabmap {

class RTABMAP_EXP OptimizerGTSAM : public Optimizer
{
public:
	static bool available();

public:
	OptimizerGTSAM(const ParametersMap & parameters = ParametersMap()) :
		Optimizer(parameters),
		optimizer_(Parameters::defaultGTSAMOptimizer())
	{
		parseParameters(parameters);
	}
	virtual ~OptimizerGTSAM() {}

	virtual Type type() const {return kTypeGTSAM;}

	virtual void parseParameters(const ParametersMap & parameters);

	virtual std::map<int, Transform> optimize(
			int rootId,
			const std::map<int, Transform> & poses,
			const std::multimap<int, Link> & edgeConstraints,
			cv::Mat & outputCovariance,
			std::list<std::map<int, Transform> > * intermediateGraphes = 0,
			double * finalError = 0,
			int * iterationsDone = 0);

private:
	int optimizer_;
	typedef gtsam::RangeFactor<gtsam::Pose2, gtsam::Pose2> RobotRangeFactor2D;
	typedef gtsam::RangeFactor<gtsam::Pose3, gtsam::Pose3> RobotRangeFactor3D;
	typedef gtsam::RangeFactor<gtsam::Pose2, gtsam::Point2> LandmarkRangeFactor2D;
	typedef gtsam::RangeFactor<gtsam::Pose3, gtsam::Point3> LandmarkRangeFactor3D;
	typedef gtsam::RangeFactorWithTransform<gtsam::Pose2, gtsam::Pose2> RobotRangeFactorWithTransform2D;
	typedef gtsam::RangeFactorWithTransform<gtsam::Pose3, gtsam::Pose3> RobotRangeFactorWithTransform3D;
	typedef gtsam::RangeFactorWithTransform<gtsam::Pose2, gtsam::Point2> LandmarkRangeFactorWithTransform2D;
	typedef gtsam::RangeFactorWithTransform<gtsam::Pose3, gtsam::Point3> LandmarkRangeFactorWithTransform3D;


};

} /* namespace rtabmap */
#endif /* OPTIMIZERGTSAM_H_ */
