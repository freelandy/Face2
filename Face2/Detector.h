#pragma once
#include "include/FaceDetector2.h"

#include "Utils.h"

#pragma comment (lib,"lib/SeetaFaceDetector200.lib")

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;
using namespace System::IO;

namespace Face2
{
	public ref class Detector
	{
	public:
		Detector();
		Detector(String^ model_file_name);
		~Detector();

		List<Rectangle>^ Detect(Bitmap^ bmp);
		//List<Rectangle>^ FastDetect(Bitmap^ bmp);

	private:
		seeta::FaceDetector2* detector = nullptr;
	};
}
