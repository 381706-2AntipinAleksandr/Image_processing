#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "Filter.h"

using namespace cv;

int main(int argc, char** argv)
{
	try
	{
		std::string sourse = argv[1];
		std::string typeOfFilter = argv[2];
		Mat Image = imread(sourse, 0);
		Mat Image2 = Image;
		namedWindow("Display Window", WINDOW_AUTOSIZE);
		imshow("Display Window", Image);
		waitKey(0);
		cvtColor(Image, Image2, COLOR_BGR2GRAY);
		imshow("Display Window", Image2);
		waitKey(0);
	}
	catch (const std::exception&)
	{
		std::cout << "Error! Wrong image sourse or type of filter" << std::endl;
	}

	/////////////////////////////////////////////

	//Mat Image = imread("C:\\Users\\aleks\\Desktop\\Учеба\\Программирование\\Web-Projects\\practice2\\img\\uber_car.png", 0);
	return 0;
}