#pragma once
#include "include/PointDetector2.h"

#include "Utils.h"

#pragma comment (lib,"lib/SeetaPointDetector200.lib")

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;
using namespace System::IO;

namespace Face2
{
	public ref class Aligner
	{
	public:
		Aligner();
		Aligner(String^ model_file_name);
		~Aligner();

		List<PointF>^ Align(Bitmap^ bmp, Rectangle^ face);

	private:
		seeta::PointDetector2* aligner = nullptr;
	};
}

