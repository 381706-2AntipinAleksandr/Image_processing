#pragma once
#include "Filter.h"

#define OPENCV 0
#define AVERAGE 1
#define LIGHTNESS 2
#define LUMINOSITY 3
#define PHOTOSHOP 4
#define ITU_R 5
#define MAX_F 6
#define MIN_F 7
#define LAST 8


class GrayFilter : public Filter
{
	int nomber;
public:
	GrayFilter() : Filter() {};
	GrayFilter(cv::Mat bmp, int nomber);
	cv::Mat changeColor() override;
	cv::Mat changeColorOpencv();
	cv::Vec3b changeColorAverage(cv::Vec3b color);
	cv::Vec3b changeColorLightness(cv::Vec3b color);
	cv::Vec3b changeColorLuminosity(cv::Vec3b color);
	cv::Vec3b changeColorPhotoshopAndGIMP(cv::Vec3b color);
	cv::Vec3b changeColorITU_R(cv::Vec3b color);
	cv::Vec3b changeColorMax(cv::Vec3b color);
	cv::Vec3b changeColorMin(cv::Vec3b color);
	cv::Vec3b changeColorLast(cv::Vec3b color);
};
