#pragma once
#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"

typedef short s_int;

class Filter
{
protected:
	cv::Mat bmp;
public:
	Filter();
	Filter(cv::Mat bmp);
	~Filter();
	virtual cv::Mat changeColor();
};

