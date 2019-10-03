//#include "blackAndWhiteFilter.h"
//
//
//Bitmap^ BaWF::changeColor()
//{
//	for (int i = 0; i < bmp->Width; i++)
//		for (int j = 0; j < bmp->Height; j++)
//		{
//			Color color = bmp->GetPixel(i, j);
//			s_int weight = (color.R + color.G + color.B) / 3;
//			if (weight < 128)
//				color = Color::FromArgb(0, 0, 0);
//			else
//				color = Color::FromArgb(255, 255, 255);
//			bmp->SetPixel(i, j, color);
//		}
//	return bmp;
//}