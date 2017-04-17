/**
 * @file util.h
 * @brief Monocular SLAM with April tags and iSAM
 * @author: Michael Kaess
 *
 */
#include <opencv2/opencv.hpp>
#include <Eigen/Dense>
#include <map>
#include <string>
#include <bot_lcmgl_client/lcmgl.h>
#include <GL/gl.h>

using namespace Eigen;
using namespace cv;
using namespace std;

map<int, Scalar> get_color_table();

void draw_point_lcmgl(bot_lcmgl_t* lcmgl_, Eigen::Vector3d pt,
			float r = 1, float g = 0, float b = 0);
void draw_line_lcmgl(bot_lcmgl_t* lcmgl_, Eigen::Vector3d pt0, Eigen::Vector3d pt1,
		float r = 1, float g = 0, float b = 0);
void draw_pose_lcmgl(bot_lcmgl_t* lcmgl_, Eigen::Matrix4d pose,
			float r=1, float g=0, float b=1);
void draw_pose_lcmgl(bot_lcmgl_t* lcmgl_,
		Eigen::Vector3d trans, Eigen::Vector3d rpy,
			float r=1, float g=0, float b=1);
