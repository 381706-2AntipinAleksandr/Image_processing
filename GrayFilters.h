#pragma once
#include "Filter.h"
//#include "opencv2/core/core.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"

#define OPENCV 0
#define AVERAGE 1
#define LIGHTNESS 2
#define LUMINOSITY 3
//#define PHOTOSHOP 4
//#define ITU_R 5
//#define MAX_F 6
//#define MIN_F 7
//#define LAST 8
//
//
//public ref class GrayFilter : public Filter
//{
//	int nomber;
//public:
//	GrayFilter() : Filter() {};
//	GrayFilter(Bitmap^ bmp, int nomber);
//	Bitmap^ changeColor() override;
//	Color^ changeColorOpencv(Bitmap^ bmp);
//	Color^ changeColorAverage(Color^ color);
//	Color^ changeColorLightness(Color^ color);
//	Color^ changeColorLuminosity(Color^ color);
//	Color^ changeColorPhotoshopAndGIMP(Color^ color);
//	Color^ changeColorITU_R(Color^ color);
//	Color^ changeColorMax(Color^ color);
//	Color^ changeColorMin(Color^ color);
//	Color^ changeColorLast(Color^ color);
//};
