#pragma once
#include "include/CStruct.h"

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;

namespace Face2
{
	public ref class Utils
	{
	public:
		Utils();

	public:
		static unsigned char* Bitmap2Data(Bitmap^ bmp);
		static Bitmap^ Data2Bitmap(int width, int height, unsigned char* data);
		static SeetaImageData Utils::Bitmap2SeetaImageData(Bitmap^ bmp);
		static SeetaRect Rectangle2SeetaRect(Rectangle^ rect);
		static SeetaPointF PointF2SeetaPointF(PointF pt);
	};
}

