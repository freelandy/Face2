#pragma once
#include "include/FaceRecognizer.h"

#include "Utils.h"

#pragma comment (lib,"lib/SeetaFaceRecognizer200.lib")

using namespace System;
using namespace System::Collections::Generic;
using namespace System::Drawing;
using namespace System::Drawing::Imaging;
using namespace System::IO;

namespace Face2
{
	public ref class Recognizer
	{
	public:
		Recognizer();
		Recognizer(String^ model_file_name);
		~Recognizer();

		float Verify(Bitmap^ face1, List<PointF>^ pts1, Bitmap^ face2, List<PointF>^ pts2);
		int Identify(Bitmap^ face, List<PointF>^ pts, float% similarity);
		array<float>^ Identify(Bitmap^ face, List<PointF>^ pts);
		int Register(Bitmap^ face, List<PointF>^ pts);
		void Clear();
		int GetMaxRegisterIndex();


	private:
		seeta::FaceRecognizer2* recognizer = nullptr;
	};
}
