#include "GrayFilters.h"

GrayFilter::GrayFilter(cv::Mat bmp, int nomber) : Filter(bmp)
{
	this->nomber = nomber;
	for (int i = 0; i < 256; i++)
		hist[i] = 0;
}

cv::Mat GrayFilter::changeColor()
{
	if (nomber == OPENCV)
		return changeColorOpencv();
	for (int i = 0; i < bmp.rows; i++)
		for (int j = 0; j < bmp.cols; j++)
		{
			cv::Vec3b color = bmp.at<cv::Vec3b>(i, j);
			switch (nomber)
			{
			case AVERAGE:
				color = changeColorAverage(color);
				break;
			case LIGHTNESS:
				color = changeColorLightness(color);
				break;
			case LUMINOSITY:
				color = changeColorLuminosity(color);
				break;
			case PHOTOSHOP:
				color = changeColorPhotoshopAndGIMP(color);
				break;
			case ITU_R:
				color = changeColorITU_R(color);
				break;
			case MAX_F:
				color = changeColorMax(color);
				break;
			case MIN_F:
				color = changeColorMin(color);
				break;
			case LAST:
				color = changeColorLast(color);
				break;
			default:
				break;
			}
			bmp.at<cv::Vec3b>(i, j) = color;
			hist[bmp.at<cv::Vec3b>(i, j)[0]]++;
		}
	printHist();
	return bmp;
}

cv::Mat GrayFilter::changeColorOpencv()
{
	cv::Mat Image;
	cv::cvtColor(bmp, Image, cv::COLOR_RGB2GRAY);
	return Image;
}

cv::Vec3b GrayFilter::changeColorAverage(cv::Vec3b color)
{
	s_int weight = (color[0] + color[1] + color[2]) / 3;
	return cv::Vec3b(weight, weight, weight);
}

cv::Vec3b GrayFilter::changeColorLightness(cv::Vec3b color)
{
	s_int max = color[0], min = color[1];
	if (color[1] > color[0])
	{
		max = color[1];
		min = color[0];
	}
	if (color[2] > color[0])
		max = color[2];
	if (color[2] < color[1])
		min = color[2];
	s_int weight = (max + min) / 2;
	return cv::Vec3b(weight, weight, weight);
}

cv::Vec3b GrayFilter::changeColorLuminosity(cv::Vec3b color)
{
	s_int weight = 0.21 * color[0] + 0.72 * color[1] + 0.07 * color[2];
	return cv::Vec3b(weight, weight, weight);
}

cv::Vec3b GrayFilter::changeColorPhotoshopAndGIMP(cv::Vec3b color)
{
	s_int weight = 0.3 * color[0] + 0.59 * color[1] + 0.11 * color[2];
	return cv::Vec3b(weight, weight, weight);
}

cv::Vec3b GrayFilter::changeColorITU_R(cv::Vec3b color)
{
	s_int weight = 0.2126 * color[0] + 0.7152 * color[1] + 0.0722 * color[2];
	return cv::Vec3b(weight, weight, weight);
}

cv::Vec3b GrayFilter::changeColorMax(cv::Vec3b color)
{
	s_int max = color[0];
	if (color[1] > color[0])
		max = color[1];
	else if (color[2] > color[0])
		max = color[2];
	return cv::Vec3b(max, max, max);
}

cv::Vec3b GrayFilter::changeColorMin(cv::Vec3b color)
{
	s_int min = color[0];
	if (color[1] < color[0])
		min = color[1];
	else if (color[2] < color[0])
		min = color[2];
	return cv::Vec3b(min, min, min);
}

cv::Vec3b GrayFilter::changeColorLast(cv::Vec3b color)
{
	s_int weight = 0.2952 * color[0] + 0.5547 * color[1] + 0.148 * color[2];
	return cv::Vec3b(weight, weight, weight);
}

void GrayFilter::printHist()
{
	for (int i = 0; i < 256; i++)
		printf("weight %d - %d,\t", i, hist[i]);
}
