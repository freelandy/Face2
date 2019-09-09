#include "pch.h"
#include "Utils.h"

namespace Face2
{
	Utils::Utils()
	{
	}

	unsigned char* Utils::Bitmap2Data(Bitmap^ bmp)
	{
		System::Drawing::Rectangle rect = System::Drawing::Rectangle(0, 0, bmp->Width, bmp->Height);
		BitmapData^ bmpData = bmp->LockBits(rect, System::Drawing::Imaging::ImageLockMode::ReadWrite, bmp->PixelFormat);
		unsigned char* pData = (unsigned char*)bmpData->Scan0.ToPointer();

		bmp->UnlockBits(bmpData);

		return pData;
	}

	Bitmap^ Utils::Data2Bitmap(int width, int height, unsigned char* data)
	{
		System::Drawing::Bitmap^ bmp = gcnew Bitmap(width,height,
													width,
													System::Drawing::Imaging::PixelFormat::Format8bppIndexed,
													(System::IntPtr)data);

		return bmp;
	}

	
	SeetaImageData Utils::Bitmap2SeetaImageData(Bitmap^ bmp)
	{
		int width = bmp->Width;
		int height = bmp->Height;
		int channels = bmp->PixelFormat == PixelFormat::Format8bppIndexed ? 1 : 3;
		unsigned char* data = Bitmap2Data(bmp);

		SeetaImageData img;
		img.width = width;
		img.height = height;
		img.channels = channels;
		img.data = data;

		return img;
	}

	SeetaRect Utils::Rectangle2SeetaRect(Rectangle^ rect)
	{
		SeetaRect seeta_rect;
		seeta_rect.x = rect->X;
		seeta_rect.y = rect->Y;
		seeta_rect.width = rect->Width;
		seeta_rect.height = rect->Height;

		return seeta_rect;
	}

	SeetaPointF Utils::PointF2SeetaPointF(PointF pt)
	{
		SeetaPointF seeta_point;
		seeta_point.x = pt.X;
		seeta_point.y = pt.Y;

		return seeta_point;
	}

}