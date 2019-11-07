#include <algorithm>
#include "Filter.h"

class MidPointFilter : public Filter {
 private:
  std::vector<int> masR, masG, masB;
  int midR, midG, midB;
  int radius;
  int mW;
  double dis;

 public:
  MidPointFilter() : Filter(){};
  MidPointFilter(cv::Mat bmp, int radius);
  cv::Mat changeColor() override;
  void getMidPoint(int i, int j);
  void outMetrics();
  int getMW();
  double getDispersion();
};