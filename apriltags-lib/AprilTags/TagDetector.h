#ifndef TAGDETECTOR_H
#define TAGDETECTOR_H

#include <vector>

#include "opencv2/opencv.hpp"

#include "AprilTags/TagDetection.h"
#include "AprilTags/TagFamily.h"
#include "AprilTags/FloatImage.h"
#include "AprilTags/Segment.h"
#include "AprilTags/Quad.h"

namespace AprilTags {

class TagDetector {
public:
	
	const TagFamily thisTagFamily;

	//! Constructor
  // note: TagFamily is instantiated here from TagCodes
	TagDetector(const TagCodes& tagCodes) : thisTagFamily(tagCodes) {}
	
	std::vector<TagDetection> extractTags(const cv::Mat& image);
	
	// Step 1-2
	void extractFloatImages(const cv::Mat& image, std::vector<FloatImage> &float_images);

	// Step 3-6
	void extractSegments(
			const cv::Mat& image, const cv::Mat& im_mask,
			std::vector<FloatImage> float_images,
			std::vector<Segment> & segments);

	// Step 7 twist
	void extractQuads(
			const cv::Mat& image, std::vector<Segment> segments,
			std::vector<Quad> & quads);

};

} // namespace

#endif
