/**
 * @file util.h
 * @brief Monocular SLAM with April tags and iSAM
 * @author: Michael Kaess
 *
 */
#include "lcmgl-util.h"

using namespace Eigen;
using namespace std;
using namespace cv;


cv::Scalar rc() { // get a random pastel color
  Scalar s = cv::Scalar(150 + (float)rand()/((float)RAND_MAX/(100)),
                    	150 + (float)rand()/((float)RAND_MAX/(100)),
                    	150 + (float)rand()/((float)RAND_MAX/(100)));
  Scalar s1 = Scalar(s[0]/255, s[1]/255, s[2]/255);
  return s1;
}

cv::Scalar rc_dark() { // get a random pastel color
  Scalar s = cv::Scalar(75 + (float)rand()/((float)RAND_MAX/(75)),
                    	75 + (float)rand()/((float)RAND_MAX/(75)),
                    75 + (float)rand()/((float)RAND_MAX/(75)));
  Scalar s1 = Scalar(s[0]/255, s[1]/255, s[2]/255);
  return s1;
}

cv::Scalar rc_bright() { // get a random pastel color
	Scalar s = cv::Scalar(200 + (float)rand()/((float)RAND_MAX/(50)),
			200 + (float)rand()/((float)RAND_MAX/(50)),
			200 + (float)rand()/((float)RAND_MAX/(50)));
	Scalar s1 = Scalar(s[0]/255, s[1]/255, s[2]/255);
	return s1;
}

map<int, Scalar> get_color_table(){
	map<int, Scalar> color_table;

	for(int i = 0; i < 36; i++){
		if (i % 2 == 0)
			color_table[i] = rc_dark();
		else
			color_table[i] = rc_bright();
	}

//	color_table[0] = Scalar(255/255, 0/255, 0/255);
//	color_table[1] = Scalar(204/255,0/255, 0/255);
//	color_table[2] = Scalar(204/255,160/255,153/255);
//	color_table[3] = Scalar(204/255, 112/255, 51/255);
//	color_table[4] = Scalar(89/255, 49/255, 22/255);
//	color_table[5] = Scalar(102/255, 87/255, 77/255);
//	color_table[6] = Scalar(204/255, 180/255, 153/255);
//	color_table[7] = Scalar(204/255, 153/255, 51/255);
//	color_table[8] = Scalar(51/255, 38/255, 13/255);
//	color_table[9] = Scalar(83/255, 89/255, 0/255);
//	color_table[10] = Scalar(222/255, 230/255, 115/255);
//	color_table[11] = Scalar(112/255, 204/255, 51/255);
//	color_table[12] = Scalar(200/255, 255/255, 191/255);
//	color_table[13] = Scalar(110/255, 140/255, 105/255);
//	color_table[14] = Scalar(22/255, 89/255, 22/255);
//	color_table[15] = Scalar(38/255, 51/255, 43/255);
//	color_table[16] = Scalar(0/255, 230/255, 184/255);
//	color_table[17] = Scalar(0/255, 115/255, 107/255);
//	color_table[18] = Scalar(153/255, 204/255, 201/255);
//	color_table[19] = Scalar(0/255, 204/255, 255/255);
//	color_table[20] = Scalar(51/255, 92/255, 102/255);
//	color_table[21] = Scalar(0/255, 119/255, 179/255);
//	color_table[22] = Scalar(16/255, 41/255, 64/255);
//	color_table[23] = Scalar(0/255, 87/255, 217/255);
//	color_table[24] = Scalar(128/255, 162/255, 255/255);
//	color_table[25] = Scalar(54/255, 0/255, 204/255);
//	color_table[26] = Scalar(36/255, 0/255, 89/255);
//	color_table[27] = Scalar(179/255, 128/255, 255/255);
//	color_table[28] = Scalar(85/255, 51/255, 102/255);
//	color_table[29] = Scalar(46/255, 26/255, 51/255);
//	color_table[30] = Scalar(190/255, 0/255, 204/255);
//	color_table[31] = Scalar(255/255, 128/255, 229/255);
//	color_table[32] = Scalar(204/255, 0/255, 136/255);
//	color_table[33] = Scalar(204/255, 153/255, 187/255);
//	color_table[34] = Scalar(89/255, 22/255, 49/255);
//	color_table[35] = Scalar(51/255, 38/255, 43/255);
//	color_table[36] = Scalar(255/255, 128/255, 162/255);
//	color_table[37] = Scalar(102/255, 77/255, 83/255);
//	color_table[38] = Scalar(89/255, 0/255, 12/255);
//	color_table[39] = Scalar(217/255, 54/255, 76/255);

	color_table[0] = Scalar(1, 0, 0);		// red
	color_table[1] = Scalar(0, 1, 0);		// green
	color_table[2] = Scalar(0, 0, 1);		// blue
	color_table[3] = Scalar(1, 0, 1);
	color_table[4] = Scalar(0, 1, 1);
	color_table[5] = Scalar(1, 1, 0);
	color_table[6] = Scalar(0.5, 0, 0);
	color_table[7] = Scalar(0, 0.5, 0);
	color_table[8] = Scalar(0, 0, 0.5);
	color_table[9] = Scalar(0.5, 0.5, 0);
	color_table[10] = Scalar(0, 0.5, 0.5);
	color_table[11] = Scalar(0.5, 0, 0.5);
	color_table[12] = Scalar(0.75, 0, 0);
	color_table[13] = Scalar(0, 0.75, 0);
	color_table[14] = Scalar(0, 0, 0.75);
	color_table[15] = Scalar(0.75, 0.75, 0);
	color_table[16] = Scalar(0.75, 0, 0.75);
	color_table[17] = Scalar(0, 0.75, 0.75);
	color_table[18] = Scalar(0.25, 0, 0);
	color_table[19] = Scalar(0, 0.25, 0);
	color_table[20] = Scalar(0, 0, 0.25);
	color_table[21] = Scalar(0.25, 0.25, 0);
	color_table[22] = Scalar(0, 0.25, 0.25);
	color_table[23] = Scalar(0.25, 0, 0.25);

	color_table[24] = Scalar(0.5, 0, 0);
	color_table[25] = Scalar(0, 0.5, 0);
	color_table[26] = Scalar(0, 0, 0.5);
	color_table[27] = Scalar(0.5, 0.5, 0);
	color_table[28] = Scalar(0, 0.5, 0.5);
	color_table[29] = Scalar(0.5, 0, 0.5);

	color_table[30] = Scalar(1, 0, 0);		// red
	color_table[31] = Scalar(0, 1, 0);		// green
	color_table[32] = Scalar(0, 0, 1);		// blue
	color_table[33] = Scalar(1, 1, 0);
	color_table[34] = Scalar(1, 0, 1);
	color_table[35] = Scalar(0, 1, 1);
	color_table[36] = Scalar(0.5, 0, 0);
	color_table[37] = Scalar(0, 0.5, 0);
	color_table[38] = Scalar(0, 0, 0.5);
	color_table[39] = Scalar(0.5, 0.5, 0);
	color_table[40] = Scalar(0, 0.5, 0.5);
	color_table[41] = Scalar(0.5, 0, 0.5);
	color_table[42] = Scalar(0.75, 0, 0);
	color_table[43] = Scalar(0, 0.75, 0);
	color_table[44] = Scalar(0, 0, 0.75);
	color_table[45] = Scalar(0.75, 0.75, 0);
	color_table[46] = Scalar(0.75, 0, 0.75);
	color_table[47] = Scalar(0, 0.75, 0.75);
	color_table[48] = Scalar(0.25, 0, 0);
	color_table[49] = Scalar(0, 0.25, 0);
	
	return color_table;
}

void draw_point_lcmgl(bot_lcmgl_t* lcmgl_, Eigen::Vector3d pt,
		float r, float g, float b){

	bot_lcmgl_translated(lcmgl_, 0, 0, 0);
	bot_lcmgl_line_width(lcmgl_, 2.0f);
	bot_lcmgl_point_size(lcmgl_, 7.0f);
	bot_lcmgl_begin(lcmgl_, LCMGL_POINTS);

	bot_lcmgl_color3f(lcmgl_, r, g, b);
	bot_lcmgl_vertex3f(lcmgl_, pt[0], pt[1], pt[2]);

	bot_lcmgl_end(lcmgl_);
}

void draw_line_lcmgl(bot_lcmgl_t* lcmgl_, Eigen::Vector3d pt0, Eigen::Vector3d pt1,
		float r, float g, float b){

	bot_lcmgl_translated(lcmgl_, 0, 0, 0);
	bot_lcmgl_line_width(lcmgl_, 2.0f);
	bot_lcmgl_point_size(lcmgl_, 7.0f);
	bot_lcmgl_color3f(lcmgl_, r, g, b);

	bot_lcmgl_begin(lcmgl_, GL_LINE_STRIP);
	bot_lcmgl_vertex3f(lcmgl_, pt0[0], pt0[1], pt0[2]);
	bot_lcmgl_vertex3f(lcmgl_, pt1[0], pt1[1], pt1[2]);
	bot_lcmgl_end(lcmgl_);
}

void draw_pose_lcmgl(bot_lcmgl_t* lcmgl_, Eigen::Matrix4d pose,
			float r, float g, float b){

	float normal_length = 0.4;

	bot_lcmgl_translated(lcmgl_, 0, 0, 0);
	bot_lcmgl_line_width(lcmgl_, 2.0f);
	bot_lcmgl_point_size(lcmgl_, 7.0f);
	bot_lcmgl_color3f(lcmgl_, r, g, b);

	Eigen::Vector3d pt;
	pt << pose(0, 3), pose(1, 3), pose(2, 3);

	Eigen::Matrix4d M_fd, M_left, M_up;
	Eigen::Matrix4d T_fd, T_left, T_up;
	T_fd << 1, 0, 0, normal_length,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1;
	M_fd = pose * T_fd;

	T_left << 	1, 0, 0, 0,
			0, 1, 0, normal_length/2,
			0, 0, 1, 0,
			0, 0, 0, 1;
	M_left = pose * T_left;

	T_up << 1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, normal_length/2,
			0, 0, 0, 1;
	M_up = pose * T_up;

	Eigen::Vector3d pt_fd, pt_left, pt_up;
	pt_fd << M_fd(0, 3), M_fd(1, 3), M_fd(2, 3);
	pt_left << M_left(0, 3), M_left(1, 3), M_left(2, 3);
	pt_up << M_up(0, 3), M_up(1, 3), M_up(2, 3);

	bot_lcmgl_begin(lcmgl_, GL_LINE_STRIP);
	bot_lcmgl_vertex3f(lcmgl_, pt[0], pt[1], pt[2]);
	bot_lcmgl_vertex3f(lcmgl_, pt_fd[0], pt_fd[1], pt_fd[2]);
	bot_lcmgl_end(lcmgl_);

	bot_lcmgl_begin(lcmgl_, GL_LINE_STRIP);
	bot_lcmgl_vertex3f(lcmgl_, pt[0], pt[1], pt[2]);
	bot_lcmgl_vertex3f(lcmgl_, pt_left[0], pt_left[1], pt_left[2]);
	bot_lcmgl_end(lcmgl_);

	bot_lcmgl_begin(lcmgl_, GL_LINE_STRIP);
	bot_lcmgl_vertex3f(lcmgl_, pt[0], pt[1], pt[2]);
	bot_lcmgl_vertex3f(lcmgl_, pt_up[0], pt_up[1], pt_up[2]);
	bot_lcmgl_end(lcmgl_);

	bot_lcmgl_begin(lcmgl_, GL_POINTS);
	bot_lcmgl_vertex3f(lcmgl_, pt[0], pt[1], pt[2]);
	bot_lcmgl_end(lcmgl_);
}
