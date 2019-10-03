//#include "GrayFilters.h"
//
//GrayFilter::GrayFilter(Bitmap^ bmp, int nomber) : Filter(bmp)
//{
//	this->nomber = nomber;
//}
//
//Bitmap^ GrayFilter::changeColor()
//{
//	for (int i = 0; i < bmp->Width; i++)
//		for (int j = 0; j < bmp->Height; j++)
//		{
//			Color color = bmp->GetPixel(i, j);
//			switch (nomber)
//			{
//			case AVERAGE:
//				color = *(changeColorAverage(color));
//				break;
//			case LIGHTNESS:
//				color = *(changeColorLightness(color));
//				break;
//			case LUMINOSITY:
//				color = *(changeColorLuminosity(color));
//				break;
//			case PHOTOSHOP:
//				color = *(changeColorPhotoshopAndGIMP(color));
//				break;
//			case ITU_R:
//				color = *(changeColorITU_R(color));
//				break;
//			case MAX_F:
//				color = *(changeColorMax(color));
//				break;
//			case MIN_F:
//				color = *(changeColorMin(color));
//				break;
//			case LAST:
//				color = *(changeColorLast(color));
//				break;
//			default:
//				break;
//			}
//			bmp->SetPixel(i, j, color);
//		}
//	return bmp;
//}
//
//Color^ GrayFilter::changeColorOpencv(Bitmap^ bmp)
//{
//	//cv::Mat* image = new cv::Mat(bmp->Width, bmp->Height, CvType.CV_8UC4);
//	//cv::
//	//cv::cvtColor(bmp, gray, CV_BGR2GRAY);
//	return nullptr;
//}
//
//Color^ GrayFilter::changeColorAverage(Color^ color)
//{
//	s_int weight = (color->R + color->G + color->B) / 3;
//	return Color::FromArgb(weight, weight, weight);
//}
//
//Color^ GrayFilter::changeColorLightness(Color^ color)
//{
//	s_int max = color->R, min = color->G;
//	if (color->G > color->R)
//	{
//		max = color->G;
//		min = color->R;
//	}
//	if (color->B > color->R)
//		max = color->G;
//	if (color->B < color->G)
//		min = color->B;
//	s_int weight = (max + min) / 2;
//	return Color::FromArgb(weight, weight, weight);
//}
//
//Color^ GrayFilter::changeColorLuminosity(Color^ color)
//{
//	s_int weight = 0.21 * color->R + 0.72 * color->G + 0.07 * color->B;
//	return Color::FromArgb(weight, weight, weight);
//}
//
//Color^ GrayFilter::changeColorPhotoshopAndGIMP(Color^ color)
//{
//	s_int weight = 0.3 * color->R + 0.59 * color->G + 0.11 * color->B;
//	return Color::FromArgb(weight, weight, weight);
//}
//
//Color^ GrayFilter::changeColorITU_R(Color^ color)
//{
//	s_int weight = 0.2126 * color->R + 0.7152 * color->G + 0.0722 * color->B;
//	return Color::FromArgb(weight, weight, weight);
//}
//
//Color^ GrayFilter::changeColorMax(Color^ color)
//{
//	s_int max = color->R;
//	if (color->G > color->R)
//		max = color->G;
//	else if (color->B > color->R)
//		max = color->B;
//	return Color::FromArgb(max, max, max);
//}
//
//Color^ GrayFilter::changeColorMin(Color^ color)
//{
//	s_int min = color->R;
//	if (color->G < color->R)
//		min = color->G;
//	else if (color->B < color->R)
//		min = color->B;
//	return Color::FromArgb(min, min, min);
//}
//
//Color^ GrayFilter::changeColorLast(Color^ color)
//{
//	s_int weight = 0.2952 * color->R + 0.5547 * color->G + 0.148 * color->B;
//	return Color::FromArgb(weight, weight, weight);
//}