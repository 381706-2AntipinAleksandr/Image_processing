#pragma once
#include "Filter.h"
#include <algorithm>

class MedianFilter : public Filter
{
private:
    std::vector<int> masR, masG, masB;
    int medR, medG, medB;
    int radius;
public:
    MedianFilter() : Filter() {};
    MedianFilter(cv::Mat bmp, int radius);
    cv::Mat changeColor() override;
    void getMedian(int i, int j);
};