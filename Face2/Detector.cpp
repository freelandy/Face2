#include "pch.h"
#include "Detector.h"
#include <fstream>
#include <iostream>

namespace Face2
{
	Detector::Detector()
	{
		
	}

	Detector::Detector(String^ model_file_name)
	{
		char* model = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(model_file_name);
		this->detector = new seeta::FaceDetector2(model);
	}

	Detector::~Detector()
	{
		if (this->detector != nullptr)
		{
			delete this->detector;
			this->detector = nullptr;
		}
	}

	List<Rectangle>^ Detector::Detect(Bitmap^ bmp)
	{
		SeetaImageData img = Utils::Bitmap2SeetaImageData(bmp);

		int num = 0;
		SeetaRect* rects = this->detector->Detect(img, &num);

		List<Rectangle>^ faces = gcnew List<Rectangle>();

		for (int i = 0; i < num; i++)
		{
			Rectangle face;
			face.X = rects[i].x;
			face.Y = rects[i].y;
			face.Width = rects[i].width;
			face.Height = rects[i].height;

			faces->Add(face);
		}

		return faces;
	}

	//List<Rectangle>^ Detector::FastDetect(Bitmap^bmp)
	//{
	//	// convert bitmap to unsigned char data, bmp must be a gray scale image
	//	Rectangle^ rect = gcnew Rectangle(0, 0, bmp->Width, bmp->Height);
	//	BitmapData^ bmpData = bmp->LockBits(*rect, ImageLockMode::ReadWrite, bmp->PixelFormat);
	//	unsigned char* grayData = (unsigned char*)bmpData->Scan0.ToPointer();


	//	// copied from libfacedetect demo
	//	int * pResults = nullptr;
	//	int buffer_size = 0x20000;
	//	//pBuffer is used in the detection functions.
	//	//If you call functions in multiple threads, please create one buffer for each thread!

	//	unsigned char * pBuffer = new unsigned char[buffer_size]; // (unsigned char *)malloc(buffer_size);
	//	if (!pBuffer)
	//	{
	//		return nullptr;
	//	}


	//	///////////////////////////////////////////
	//	// frontal face detection designed for video surveillance / 68 landmark detection
	//	// it can detect faces with bad illumination.
	//	//////////////////////////////////////////
	//	//!!! The input image must be a gray one (single-channel)
	//	//!!! DO NOT RELEASE pResults !!!
	//	// step must be bmpData->stride, not 1
	//	// pBuffer must not be released
	//	pResults = facedetect_frontal_surveillance(pBuffer, grayData, bmpData->Stride, bmpData->Height, bmpData->Stride, 1.2f, 2, 5, 0, 0);


	//	int num_faces = (pResults ? *pResults : 0);

	//	List<Rectangle>^ faces = gcnew List<Rectangle>();
	//	for (int i = 0; i < num_faces; i++)
	//	{
	//		short * p = ((short*)(pResults + 1)) + 142 * i;
	//		int x = p[0];
	//		int y = p[1];
	//		int w = p[2];
	//		int h = p[3];
	//		//int neighbors = p[4];
	//		//int angle = p[5];

	//		Rectangle^ face = gcnew Rectangle();
	//		face->X = x;
	//		face->Y = y;
	//		face->Width = w;
	//		face->Height = h;

	//		faces->Add(*face);

	//	}

	//	bmp->UnlockBits(bmpData);

	//	return faces;
	//}
}
