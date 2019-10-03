#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "Filter.h"
#include "GrayFilters.h"

using namespace cv;

int main(int argc, char** argv)
{
	try
	{
		std::string sourse = argv[1];
		std::string typeOfFilter = argv[2];
		Mat Image = imread(sourse, 1);
		Mat Images[8];
		Mat Image2 = imread(sourse, 1);
		GrayFilter filt(Image2, 0);
		Image2 = filt.changeColor();
		namedWindow("Sourse image", WINDOW_AUTOSIZE);
		imshow("Sourse image", Image);
		waitKey(0);
		namedWindow("Result cv image ", WINDOW_AUTOSIZE);
		imshow("Result cv image ", Image2);
		waitKey(0);
		for (int i = 0; i < 8; i++)
		{
			Images[i] = imread(sourse, 1);
			Filter* filter = new GrayFilter(Images[i], i + 1);
			filter->changeColor();
			delete filter;
			namedWindow("Result image ", WINDOW_AUTOSIZE);
			imshow("Result Window ", Images[i]);
			waitKey(0);
		}

	}
	catch (const std::exception&)
	{
		std::cout << "Error! Wrong image sourse or type of filter" << std::endl;
	}

	/////////////////////////////////////////////

	//Mat Image = imread("C:\\Users\\aleks\\Desktop\\Учеба\\Программирование\\Web-Projects\\practice2\\img\\uber_car.png", 0);
	return 0;
}