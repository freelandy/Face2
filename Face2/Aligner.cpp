#include "pch.h"
#include "Aligner.h"

namespace Face2
{
	Aligner::Aligner()
	{
	}

	Aligner::Aligner(String^ model_file_name)
	{
		char* model = (char*)(void*)System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(model_file_name);
		this->aligner = new seeta::PointDetector2(model);
	}
	Aligner::~Aligner()
	{
		if (this->aligner != nullptr)
		{
			delete this->aligner;
			this->aligner = nullptr;
		}
	}

	List<PointF>^ Aligner::Align(Bitmap^ bmp, Rectangle^ face)
	{
		SeetaImageData img = Utils::Bitmap2SeetaImageData(bmp);
		SeetaRect rect = Utils::Rectangle2SeetaRect(face);

		SeetaPointF* points = this->aligner->Detect(img, rect);

		List<PointF>^ pts = gcnew List<PointF>();
		for (int i = 0; i < 5; i++)
		{
			PointF pt;
			pt.X = points[i].x;
			pt.Y = points[i].y;

			pts->Add(pt);
		}

		return pts;
	}

}
