#include "Filter.h"

Filter::Filter()
{
}

Filter::Filter(cv::Mat bmp)
{
	this->bmp = bmp;
}

Filter::~Filter()
{
}

cv::Mat Filter::changeColor()
{
	return cv::Mat(0, 0, 0);
}