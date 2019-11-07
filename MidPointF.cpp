#include "MidPointF.h"

MidPointFilter::MidPointFilter(cv::Mat bmp, int radius) : Filter(bmp) {
  this->radius = radius;
  midR = midG = midB = 0;
  mW = 0;
  dis = 0;
}

cv::Mat MidPointFilter::changeColor() {
  for (int i = 0; i < bmp.rows; i++) {
    for (int j = 0; j < bmp.cols; j++) {
      cv::Vec3b color = bmp.at<cv::Vec3b>(i, j);
      if (i < radius || i > bmp.rows - radius - 1) {
        mW += (color[0] + color[1] + color[2]) / 3;
        continue;
      }
      if (j < radius || j > bmp.cols - radius - 1) {
        mW += (color[0] + color[1] + color[2]) / 3;
        continue;
      }
      getMidPoint(i, j);
      color[0] = midR;
      color[1] = midG;
      color[2] = midB;
      bmp.at<cv::Vec3b>(i, j) = color;
      mW += (color[0] + color[1] + color[2]) / 3;
    }
  }
  mW /= bmp.rows * bmp.cols;
  for (int i = 0; i < bmp.rows; i++)
    for (int j = 0; j < bmp.cols; j++)
      dis += pow((bmp.at<cv::Vec3b>(i, j)[0] + bmp.at<cv::Vec3b>(i, j)[1] + bmp.at<cv::Vec3b>(i, j)[2]) /3 -mW, 2);
  dis /= bmp.rows * bmp.cols;
  dis = sqrt(dis);
  return bmp;
}

void MidPointFilter::getMidPoint(int i, int j) {
  int count = 0;
  for (int a = -radius; a <= radius; a++)
    for (int b = -radius; b <= radius; b++) {
      cv::Vec3b color = bmp.at<cv::Vec3b>(i + a, j + b);
      masR.push_back(color[0]);
      masG.push_back(color[1]);
      masB.push_back(color[2]);
      count++;
    }
  
 
  midR = *std::min_element(masR.begin(), masR.end()) +
         *std::max_element(masR.begin(), masR.end()) / 2;
  midG = *std::min_element(masG.begin(), masG.end()) +
         *std::max_element(masG.begin(), masG.end()) / 2;
  midB = *std::min_element(masB.begin(), masB.end()) +
         *std::max_element(masB.begin(), masB.end()) / 2;
  masR.clear();
  masG.clear();
  masB.clear();
}

void MidPointFilter::outMetrics() {
  printf("Mat wait new - %d\n", mW);
  printf("Dispersion new - %f\n", dis);
}

int MidPointFilter::getMW() { return mW; }

double MidPointFilter::getDispersion() { return dis; }