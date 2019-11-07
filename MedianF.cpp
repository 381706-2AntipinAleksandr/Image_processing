#include "MedianF.h"

MedianFilter::MedianFilter(cv::Mat bmp, int radius) : Filter(bmp)
{
    this->radius = radius;
    //masR = new int[(2 * radius + 1) * (2 * radius + 1)];
    //masG = new int[(2 * radius + 1) * (2 * radius + 1)];
    //masB = new int[(2 * radius + 1) * (2 * radius + 1)];
    medR = medG = medB = 0;
    mW = 0;
    dis = 0;
}

cv::Mat MedianFilter::changeColor()
{
    for (int i = 0; i < bmp.rows; i++)
    {
        for (int j = 0; j < bmp.cols; j++)
        {
            cv::Vec3b color = bmp.at<cv::Vec3b>(i, j);
            if (i < radius || i > bmp.rows - radius - 1)
            {
                mW += (color[0] + color[1] + color[2]) / 3;
                continue;
            }
            if (j < radius || j > bmp.cols - radius - 1)
            {
                mW += (color[0] + color[1] + color[2]) / 3;
                continue;
            }
            getMedian(i, j);
            color[0] = medR;
            color[1] = medG;
            color[2] = medB;
            bmp.at<cv::Vec3b>(i, j) = color;
            mW += (color[0] + color[1] + color[2]) / 3;
        }
    }
    mW /= bmp.rows * bmp.cols;
    for (int i = 0; i < bmp.rows; i++)
        for (int j = 0; j < bmp.cols; j++)
            dis += pow((bmp.at<cv::Vec3b>(i, j)[0] + bmp.at<cv::Vec3b>(i, j)[1] + bmp.at<cv::Vec3b>(i, j)[2]) / 3 - mW, 2);
    dis /= bmp.rows * bmp.cols;
    dis = sqrt(dis);
    return bmp;
}

void MedianFilter::getMedian(int i, int j)
{
    int count = 0;
    for (int a = -radius; a <= radius; a++)
        for (int b = -radius; b <= radius; b++)
        {
            cv::Vec3b color = bmp.at<cv::Vec3b>(i + a, j + b);
            masR.push_back(color[0]);
            masG.push_back(color[1]);
            masB.push_back(color[2]);
            count++;
        }
    std::sort(masR.begin(), masR.end());
    std::sort(masG.begin(), masG.end());
    std::sort(masB.begin(), masB.end());
    int median = (2 * radius + 1) * (2 * radius + 1) / 2;
    medR = masR[median];
    medG = masG[median];
    medB = masB[median];
    masR.clear();
    masG.clear();
    masB.clear();
}

void MedianFilter::outMetrics()
{
    printf("Mat wait new - %d\n", mW);
    printf("Dispersion new - %f\n", dis);
}

int MedianFilter::getMW(){
    return mW; }


double MedianFilter::getDispersion(){
    return dis; }



