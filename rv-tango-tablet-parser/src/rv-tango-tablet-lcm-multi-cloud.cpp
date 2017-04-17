/**
 * @brief publish images or video stream to LCM
 * @author: Nick Wang
 *
 */

#include <signal.h>
#include <getopt.h>

#include <Eigen/Dense>
#include <boost/filesystem.hpp>

#include <opencv2/opencv.hpp>
#include <cv_bridge_lcm/rv-cv-bridge-lcm.h>
#include "lcmgl-util.h"

using namespace std;
using namespace cv;

//#define SHOW_GUI

cvBridgeLCM* cv_bridge;
cv::Mat* _image_vis;
bool _finish;

void read_frames(string image_folder,
		vector<string> &frames_to_process, vector<string> &frames_names, string ext = ".txt"){

	boost::filesystem::path image_path(image_folder);
	boost::filesystem::recursive_directory_iterator end_it;


	//load files
	for (boost::filesystem::recursive_directory_iterator it(image_path);
			it != end_it; ++it) {

		//////////////////////////////////////////////////////////
		// read image
		if (it->path().extension().string() == ext){
			frames_to_process.push_back(it->path().string());
			frames_names.push_back(it->path().stem().string());
		}
	}
	// sort the image files
	sort(frames_to_process.begin(), frames_to_process.end());
	sort(frames_names.begin(), frames_names.end());
}

Eigen::Vector4d rotate_tango_pose(Eigen::Vector4d quat_src){

	double quat_in[4] = {quat_src[1], quat_src[2], quat_src[3], quat_src[0]};
	double quat_o[4] = {0, 0, 0, 0};
	double quat_o1[4] = {0, 0, 0, 0};

	Eigen::Matrix3d rotation_matrix = Eigen::Matrix3d::Zero();
	double m[9];
	bot_quat_to_matrix(quat_in, m);
	rotation_matrix <<
		m[0], m[1], m[2],
		m[3], m[4], m[5],
		m[6], m[7], m[8];

	// rotate x -90 degree
	Eigen::Matrix3d m1 = Eigen::Matrix3d::Zero();
	m1 <<   1, 0,  0,
		0, 0,  1,
		0,-1,  0;

        // rotate y -90 degree
	Eigen::Matrix3d m2 = Eigen::Matrix3d::Zero();
	m2 <<	 0, 0,-1,
		 0, 1, 0,
	   	 1, 0, 0;

        // rotate z 180 degree
	Eigen::Matrix3d m3 = Eigen::Matrix3d::Zero();
	m3 <<	-1, 0, 0,
		 0,-1, 0,
	   	 0, 0, 1;
        // rotate z 90 degree
	Eigen::Matrix3d m4 = Eigen::Matrix3d::Zero();
	m4 <<	 0,-1, 0,
		 1, 0, 0,
	   	 0, 0, 1;
	rotation_matrix *= m1;
//	rotation_matrix *= m2;
	rotation_matrix *= m3;
//	rotation_matrix *= m4;

	double rot[9];
	rot[0] = rotation_matrix(0,0);
	rot[1] = rotation_matrix(0,1);
	rot[2] = rotation_matrix(0,2);
	rot[3] = rotation_matrix(1,0);
	rot[4] = rotation_matrix(1,1);
	rot[5] = rotation_matrix(1,2);
	rot[6] = rotation_matrix(2,0);
	rot[7] = rotation_matrix(2,1);
	rot[8] = rotation_matrix(2,2);

	bot_matrix_to_quat(rot, quat_o); 


	// switch roll and yaw
	// [r, p, y] -> [p, r, -y]
	double rpy_src[3] = {0, 0, 0};
	bot_quat_to_roll_pitch_yaw(quat_o, rpy_src);
	double rpy_dst[3] = {rpy_src[1], -rpy_src[0], -rpy_src[2]};
	bot_roll_pitch_yaw_to_quat(rpy_dst, quat_o1);
	Eigen::Vector4d quat_out;
	quat_out << quat_o1[0], quat_o1[1], quat_o1[2], quat_o1[3];
	return quat_out;
}

void termination_handler(int signum) {

}

void setup_signal_handlers(void (*handler)(int)) {
	struct sigaction new_action, old_action;
	memset(&new_action, 0, sizeof(new_action));
	new_action.sa_handler = handler;
	sigemptyset(&new_action.sa_mask);

	// Set termination handlers and preserve ignore flag.
	sigaction(SIGINT, NULL, &old_action);
	if (old_action.sa_handler != SIG_IGN)
		sigaction(SIGINT, &new_action, NULL);
	sigaction(SIGHUP, NULL, &old_action);
	if (old_action.sa_handler != SIG_IGN)
		sigaction(SIGHUP, &new_action, NULL);
	sigaction(SIGTERM, NULL, &old_action);
	if (old_action.sa_handler != SIG_IGN)
		sigaction(SIGTERM, &new_action, NULL);
}

static void
usage(const char *name)
{
	fprintf(
			stderr,
			"usage: %s [options]\n"
			"\n"
			"  -h, --help                   Shows this help text and exits\n"
			"  -i, --data-path <path>       data folder\n"
			"  -m, --mode <int>             0: Landmark, 1: IMU+Fisheye\n"
			"  -b, --beginning-frame <int>  beginning frame\n"
			"  -s, --sleep-ms               sleep milli-second default: 200 (5 Hz)\n"
			"  -l, --use-lcmgl              publish lcmgl\n"
			"  -y, --x-y-yaw              	x,y,yaw\n"
			"\n",
			name);

	exit(1);
}

int main(int argc, char** argv) {
	int use_video_device = -1; // use LCM if < 0
	char* data_folder = (char *)"";
	int mode = 0;
	long beginning_frame = 0;
	long sleep_ms = 200; // 5 Hz
	int use_lcmgl = 0;
	char* xyyaw = (char *)"";

	char* fisheye_channel = 		(char *)"IMAGE_FISHEYE";
	char* highres_rgb_channel =		(char *)"IMAGE_HIGH_RES_RGB";
	char* highres_gray_channel = 	(char *)"IMAGE_HIGH_RES_GRAY";
	char* depth_channel = 			(char *)"IMAGE_DEPTH";
	char* depth_vis_channel = 		(char *)"IMAGE_DEPTH_VIS";
	char* kinect_channel = 			(char *)"KINECT_FRAME";
	char* tango_channel = 			(char *)"TANGO_FRAME";
	char* pose_channel = 			(char *)"POSE";

	char* lcmgl_pose_channel = 		(char *)"LCMGL_POSE";
	char* lcmgl_cloud_channel = 	(char *)"LCMGL_POINT_CLOUD";

	int max_vis_pose = 3000;
	vector<Eigen::Vector3f> vis_pos;
	vector<Eigen::Matrix4d> vis_poses_mx;
	vector<vector<Eigen::Vector3f> > vis_pt_cloud;


	const char *optstring = "hi:b:s:m:l:y:";
	int c;
	struct option long_opts[] =
	{
			{ "help", no_argument, 0, 'h' },
			{ "data-path", required_argument, 0, 'i' },
			{ "mode", required_argument, 0, 'm' },
			{ "beginning-frame", required_argument, 0, 'b' },
			{ "sleep-ms", required_argument, 0, 's' },
			{ "use-lcmgl", required_argument, 0, 'l' },
			{ "x-y-yaw", required_argument, 0, 'y' },
			{ 0, 0, 0, 0 }
	};

	while ((c = getopt_long(argc, argv, optstring, long_opts, 0)) >= 0) {
		switch (c){
		case 'i':
			data_folder = strdup(optarg);
			break;
		case 'm':
			mode = atoi(optarg);
			break;
		case 's':
			sleep_ms = atol(optarg);
			break;
		case 'b':
			beginning_frame = atol(optarg);
			break;
		case 'l':
			use_lcmgl = atoi(optarg);
			break;
		case 'y':
			xyyaw = strdup(optarg);
			break;
		case 'h':
			usage(argv[0]);
			break;
		}
	}

	lcm_t* lcm = lcm_create(NULL);
	cv_bridge = new cvBridgeLCM(lcm, lcm);
	stringstream ss_channel;
	ss_channel << lcmgl_pose_channel << "_" << use_lcmgl;
	bot_lcmgl_t* lcmgl_pose = bot_lcmgl_init(lcm, ss_channel.str().c_str());

	map<int, cv::Scalar> color_table = get_color_table();

	// read rgb frame
	string vio_folder;
	if(mode == 0){
		vio_folder = "vio_rgb/";
	}else{
		vio_folder = "vio_fisheye/";
	}
	string depth_xyz_folder = "depth_xyz/";
	string rgb_folder = "rgb/";
	string fisheye_folder = "fisheye/";

	stringstream ss_vio, ss_rgb, ss_fisheye, ss_depth_xyz;
	ss_rgb << data_folder << rgb_folder;
	ss_fisheye << data_folder << fisheye_folder;
	ss_vio << data_folder << vio_folder;
	ss_depth_xyz << data_folder << depth_xyz_folder;

	string rgb_ext = ".png";
	string fisheye_ext = ".pgm";

	vector<string> frames_to_process;
	vector<string> frames_name;
	
	Eigen::Matrix4d trans_mx;
	Eigen::Vector3f trans_pos;

	trans_mx <<
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1;
	trans_pos << 0, 0, 0;

	if(std::strlen(xyyaw) > 0){
		stringstream ss;
		ss << xyyaw;
		std::string stringIn = ss.str();
		std::vector<std::string> vec(1);
		int commaCounter = 0;
		for (int i=0; i<stringIn.size(); i++) {
			if (stringIn[i] == ',') {
				vec.push_back("");
				commaCounter++;
			} else {
				vec.at(commaCounter) += stringIn[i];
			}
		}

		trans_pos[0] = std::atof(vec[0].c_str());
		trans_pos[1] = std::atof(vec[1].c_str());

		Eigen::Matrix4d xyyaw_mx;
		xyyaw_mx <<
				1, 0, 0, std::atof(vec[0].c_str()),
				0, 1, 0, std::atof(vec[1].c_str()),
				0, 0, 1, 0,
				0, 0, 0, 1;
		trans_mx *= xyyaw_mx;

	}

	// read vio folder, and find the same file name in rgb folder
	std::string target_folder = ss_vio.str();
	read_frames(target_folder, frames_to_process, frames_name);
	cout << "there are " << frames_to_process.size() << " to process" << endl;
	
	for(long f = beginning_frame; f < frames_to_process.size(); f++){

		double t_tot = (double)cvGetTickCount();

		//////////////////////////////////////////////////////////////
		// VIO Pose
		//////////////////////////////////////////////////////////////

		// vio data file
		stringstream ss;
		ss << ss_vio.str() << frames_name[f] << ".txt";

		std::ifstream vio_file(ss.str().c_str());
		string line;
		Eigen::Vector3f pos;
		Eigen::Vector4f quat;

		Eigen::Vector3f pos_r;
		Eigen::Vector4d quat_r;

		Eigen::Matrix4d pose_mx;
		bot_core_pose_t pose_t;

		while (! vio_file.eof() ){
			getline (vio_file, line);
			//
			std::string stringIn = line;
			std::vector<std::string> vec(1);
			int commaCounter = 0;
			for (int i=0; i<stringIn.size(); i++) {
				if (stringIn[i] == ',') {
					vec.push_back("");
					commaCounter++;
				} else {
					vec.at(commaCounter) += stringIn[i];
				}
			}
			if(vec.size() < 7){
				if(vec.size() > 1){
					cout << "incorrect line: " <<  vec.size() << " fields" << endl;
				}
			}else{

				// pos
				for(int i = 0; i < 3; i++){
					pos[i] = std::atof(vec[i].c_str());
				}
				// quat
				for(int i = 0; i < 4; i++){
					quat[i] = std::atof(vec[i+3].c_str());
				}

				// convert to lcm message

				pose_t.pos[0] = pos[1];
				pose_t.pos[1] = -pos[0];
				pose_t.pos[2] = pos[2];
				pos_r << pos[1], -pos[0], pos[2];
				pos_r += trans_pos;

				//TODO rotation here
				Eigen::Vector4d quat_in;
				quat_in << quat[0], quat[1], quat[2], quat[3];
				quat_r = rotate_tango_pose(quat_in);
				
				pose_t.orientation[0] = quat_r[0];
				pose_t.orientation[1] = quat_r[1];
				pose_t.orientation[2] = quat_r[2];
				pose_t.orientation[3] = quat_r[3];

				pose_t.utime = bot_timestamp_now();

				// add some delay publish the vio
				float sleep_time_vio = (float)sleep_ms / (float)(vec.size()-1);
				cv::waitKey(sleep_time_vio);
				bot_core_pose_t_publish(lcm, pose_channel, &pose_t);

				// convert to mx
				double m_t[16];
				bot_quat_pos_to_matrix(
						pose_t.orientation, pose_t.pos, m_t);
				pose_mx <<
						m_t[0],  m_t[1],  m_t[2],  m_t[3],
						m_t[4],  m_t[5],  m_t[6],  m_t[7],
						m_t[8],  m_t[9],  m_t[10], m_t[11],
						m_t[12], m_t[13], m_t[14], m_t[15];
				//cout << trans_mx << endl;
				pose_mx *= trans_mx;

			}
		}

		vio_file.close();


		if(use_lcmgl > 0){

			vis_pos.push_back(pos_r);

			cv::Scalar s = color_table[use_lcmgl];

			bot_lcmgl_push_matrix(lcmgl_pose);
			bot_lcmgl_translated(lcmgl_pose, 0, 0, 0);
			bot_lcmgl_line_width(lcmgl_pose, 10.0f);
			bot_lcmgl_point_size(lcmgl_pose, 2.0f);
			bot_lcmgl_enable(lcmgl_pose, GL_BLEND); // GL_BLEND, defined in usr/include/GL/gl.h

			draw_pose_lcmgl(lcmgl_pose, pose_mx, s[0], s[1], s[2]);

			for(int i = 0; i < vis_pos.size(); i++){
				draw_point_lcmgl(lcmgl_pose,
						Eigen::Vector3d(vis_pos[i][0], vis_pos[i][1], vis_pos[i][2]),
						s[0], s[1], s[2]);
				if(i > 0){
					draw_line_lcmgl(lcmgl_pose,
							Eigen::Vector3d(vis_pos[i-1][0], vis_pos[i-1][1], vis_pos[i-1][2]),
							Eigen::Vector3d(vis_pos[i][0], vis_pos[i][1], vis_pos[i][2]),
							s[0], s[1], s[2]);
				}
			}

			bot_lcmgl_pop_matrix(lcmgl_pose);
			bot_lcmgl_switch_buffer(lcmgl_pose);

		}


		//////////////////////////////////////////////////////////////
		// Depth XYZ
		//////////////////////////////////////////////////////////////
		//
		//			// depth data file
		//			stringstream ss_depth_xyz;
		//			ss_depth_xyz << ss2.str() << frames_name[f] << ".pcd";
		//			std::ifstream depth_xyz_file(ss_depth_xyz.str().c_str());
		//
		//			// make sure that VIO, depth_xyz, and images exists and sync
		//			if (!depth_xyz_file.is_open()){
		//				cout << "depth_xzy, and RGB are not sync, skip frame." << endl;
		//				continue;
		//			}
		//
		//			depth_xyz_file.close();

		//////////////////////////////////////////////////////////////
		// RGB image
		//////////////////////////////////////////////////////////////

		stringstream ss1;
		ss1 << ss_rgb.str() << frames_name[f] << rgb_ext;
		// check file exist
		if (boost::filesystem::exists(ss1.str() ) ){

			Mat im = imread(ss1.str());
			Mat im_vis;
			cv::cvtColor(im, im_vis, CV_BGR2RGB);

			if(use_lcmgl > 0){
				stringstream ss_rgb_channel;
				ss_rgb_channel << highres_rgb_channel << "_" << use_lcmgl;
				cv_bridge->publish_mjpg(im_vis.clone(), (char*)ss_rgb_channel.str().c_str());
			}else{
				cv_bridge->publish_mjpg(im_vis.clone(), highres_rgb_channel);
			}


		}

		//////////////////////////////////////////////////////////////
		// Fisheye image
		//////////////////////////////////////////////////////////////

		stringstream ss2;
		ss2 << ss_fisheye.str() << frames_name[f] << fisheye_ext;
		// check file exist
		if (boost::filesystem::exists(ss2.str() ) ){

			Mat im = imread(ss2.str());

			if(use_lcmgl > 0){
				stringstream ss_fisheye_channel;
				ss_fisheye_channel << fisheye_channel << "_" << use_lcmgl;
				cv_bridge->publish_mjpg(im.clone(), (char*)ss_fisheye_channel.str().c_str());
			}else{
				cv_bridge->publish_mjpg(im.clone(), fisheye_channel);
			}
		}

		//				Mat im_depth = im;
		//
		//				cv::Mat im_kinect_rgb = Mat::zeros(480, 640, CV_8UC3);
		//				cv::Mat im_kinect_depth = Mat::zeros(480, 640, CV_16UC1);
		//
		//				im_kinect_rgb.setTo(Scalar(0, 0, 255));
		//
		//        		// [y, x]: [240, 320] -> [480, 640]
		//        		for(int i = 0; i < im.cols; i++){
		//        			for(int j = 0; j < im.rows; j++){
		//        				int x = i*2;
		//        				int y = j*2;
		//        				int16_t depth = im.at<Vec3b>(j, i)[0] + 255 * im.at<Vec3b>(j, i)[1];
		//        				//cout << x << ", " << y << ": " << depth << endl;
		//        				im_kinect_depth.at<int16_t>(y, x) = depth;
		//        				im_kinect_depth.at<int16_t>(y+1, x) = depth;
		//        				im_kinect_depth.at<int16_t>(y, x+1) = depth;
		//        				im_kinect_depth.at<int16_t>(y+1, x+1) = depth;
		//        			}
		//        		}
		//
		//        		cv_bridge->publish_kinect_frame(im_kinect_rgb, im_kinect_depth, (char*)"KINECT_FRAME");



		t_tot = cvGetTickCount() - t_tot;
		cout << "Total processing time: " << t_tot/((double)cvGetTickFrequency()*1000.) << " ms." << endl;

		long delta_ms = sleep_ms - t_tot/((double)cvGetTickFrequency()*1000.);
		if(delta_ms > 0){
			cv::waitKey(delta_ms);
		}

	}

	delete cv_bridge;

	return 0;
}
