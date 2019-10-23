#include <iostream>
#include "opencv2/core.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui.hpp"
#include "Filter.h"
#include "GrayFilters.h"
#include "MedianF.h"
#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 
#include <math.h>


#define FIXELCOUNT 0.05

using namespace cv;

long long factorial(int number)
{
    if (number == 1)
        return 1;
    else
        return number * factorial(number - 1);
}

void covFuncion(double& cov, double* mW, int i1, int i2, Mat& a, Mat& b)
{
	for (int i = 0; i < a.rows; i++)
		for (int j = 0; j < a.cols; j++)
			cov = ((a.at<cv::Vec3b>(i, j)[0] + a.at<cv::Vec3b>(i, j)[1] + a.at<cv::Vec3b>(i, j)[2] / 3) - mW[i1]) * 
			((b.at<cv::Vec3b>(i, j)[0] + b.at<cv::Vec3b>(i, j)[1] + b.at<cv::Vec3b>(i, j)[2] / 3) - mW[i2]);
	cov = sqrt(cov);
}

double covFuncion1(int& mW1, int& mW2, Mat& a, Mat& b)
{
    double cov = 0;
    for (int i = 0; i < a.rows; i++)
        for (int j = 0; j < a.cols; j++)
            cov = ((a.at<cv::Vec3b>(i, j)[0] + a.at<cv::Vec3b>(i, j)[1] + a.at<cv::Vec3b>(i, j)[2] / 3) - mW1) *
            ((b.at<cv::Vec3b>(i, j)[0] + b.at<cv::Vec3b>(i, j)[1] + b.at<cv::Vec3b>(i, j)[2] / 3) - mW2);
    cov = sqrt(cov);
    return cov;
}

void ssimFunctuon(double& cov, double& ssim, double* mW, double* dis, int i1, int i2)
{
    ssim = ((2 * mW[i1] * mW[i2] + 2.55 * 2.55) * (2 * cov + 7.65 * 7.65)) / 
        ((mW[i1] * mW[i1] + mW[i2] * mW[i2] + 2.55 * 2.55) * (dis[i1] * dis[i1] + dis[i2] * dis[i2] + 7.65 * 7.65));
}

void grayFilter(std::string sourse)
{
	double cov = 0;
    double ssim = 0;
	double mW[8];
    double dis[8];
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
		GrayFilter* filter = new GrayFilter(Images[i], i + 1);
		filter->changeColor();
		mW[i] = filter->getMatWait();
        dis[i] = filter->getDispersion();
		delete filter;
		namedWindow("Result image ", WINDOW_AUTOSIZE);
		imshow("Result Window ", Images[i]);
		waitKey(0);
            
	}
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
            if (j == i)
                continue;
            else
            {
                covFuncion(cov, mW, i, j, Images[i], Images[j]);
                ssimFunctuon(cov, ssim, mW, dis, i, j);
                std::cout << "cov " << i << " and "<< j << " - "<< cov << std::endl;
                std::cout << "ssim " << i << " and " << j << " - " << ssim << std::endl;
            }
        std::cout << "--------------------------------------------------\n";
    }
}

void noise(std::string sourse)
{
    Mat Image = imread(sourse, 1);
    namedWindow("Sourse image", WINDOW_AUTOSIZE);
    imshow("Sourse image", Image);
    waitKey(0);
    int count = FIXELCOUNT * Image.rows * Image.cols;
    s_int tmp = 5;
    int brightness = 0;
    for (int i = 0; i < Image.rows; ++i)
        for (int j = 0; j < Image.cols; ++j)
        {
            ////////////////////////////////////////////////////////////////////
            /*tmp = rand() % 40;
            if (count != 0 && tmp == 0)
            {
                Image.at<cv::Vec3b>(i, j)[0] = 0;
                Image.at<cv::Vec3b>(i, j)[1] = 0;
                Image.at<cv::Vec3b>(i, j)[2] = 0;
                --count;
            }
            else if (count != 0 && tmp == 1)
            {
                Image.at<cv::Vec3b>(i, j)[0] = 255;
                Image.at<cv::Vec3b>(i, j)[1] = 255;
                Image.at<cv::Vec3b>(i, j)[2] = 255;
                --count;
            }
            else
                continue;*/
            /////////////////////////////////////////////////////////////////////
            char tmp = rand() % 255;
            brightness += (Image.at<cv::Vec3b>(i, j)[0] + Image.at<cv::Vec3b>(i, j)[1] + Image.at<cv::Vec3b>(i, j)[2]) / 3;
            int a = 4, b = 4;
            int fact = factorial(b - 1);
            double p = (pow(a, b) * pow(tmp, b - 1)) / fact * exp(-a * tmp);
            //std::cout << p << "\n";
            if (p > exp(-50))
            {
                Image.at<cv::Vec3b>(i, j)[0] = 255;
                Image.at<cv::Vec3b>(i, j)[1] = 255;
                Image.at<cv::Vec3b>(i, j)[2] = 255;
            }
        }
    brightness /= Image.rows * Image.cols;
    std::cout << "Mat wait origin - " << brightness << std::endl;
    double dis = 0;
    for (int i = 0; i < Image.rows; i++)
        for (int j = 0; j < Image.cols; j++)
            dis += pow((Image.at<cv::Vec3b>(i, j)[0] + Image.at<cv::Vec3b>(i, j)[1] + Image.at<cv::Vec3b>(i, j)[2]) / 3 - brightness, 2);
    dis /= Image.rows * Image.cols;
    dis = sqrt(dis);
    std::cout << "Dispersion origin - " << dis << std::endl;
    namedWindow("Gamma", WINDOW_AUTOSIZE);
    imshow("Gamma", Image);
    waitKey(0);
    Mat ImageOut;
    medianBlur(Image, ImageOut, 7);
    namedWindow("Median Filter CV", WINDOW_AUTOSIZE);
    imshow("Median Filter CV", ImageOut);
    waitKey(0);
    Mat originImage = Image;
    MedianFilter* f = new MedianFilter(Image, 1);
    f->changeColor();
    f->outMetrics();
    int mWN = f->getMW();
    double disN = f->getDispersion();
    double covN = covFuncion1(brightness, mWN, originImage, Image);
    double ssim = 0.0;
    double masW[] = { brightness, mWN };
    double masD[] = { dis, disN };
    ssimFunctuon(covN, ssim, masW, masD, 0, 1);
    std::cout << "Cov - " << covN << std::endl;
    std::cout << "SSIM - " << ssim << std::endl;
    namedWindow("Median Filter", WINDOW_AUTOSIZE);
    imshow("Median Filter", Image);
    waitKey(0);
    delete f;
}


int main(int argc, char** argv)
{
    srand(time(NULL));
	try
	{
		std::string sourse = argv[1];
		std::string typeOfFilter = argv[2];
        if (typeOfFilter == "Gray")
            grayFilter(sourse);
        else if (typeOfFilter == "Noises")
            noise(sourse);
	}
	catch (const std::exception&)
	{
		std::cout << "Error! Wrong image sourse or type of filter" << std::endl;
	}

	/////////////////////////////////////////////

	//Mat Image = imread("C:\\Users\\aleks\\Desktop\\Учеба\\Программирование\\Web-Projects\\practice2\\img\\uber_car.png", 0);
	return 0;
}