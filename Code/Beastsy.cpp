#include "Beastsy.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]
int main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	BitmapConverter::Beastsy form;
	Application::Run(% form);
	return 0;
}

System::Int32 BitmapConverter::Beastsy::Clamp(int value, int min, int max)
{
	if (value < min) return min;
	else if (value > max) return max;
	else return value;
}

System::Drawing::Bitmap^ BitmapConverter::Beastsy::ScaleImage(System::Drawing::Bitmap^ image, int width, int height)
{
	System::Drawing::Bitmap^ scaledImage = gcnew System::Drawing::Bitmap(width, height);

	double scaleX = static_cast<double>(image->Width) / width;
	double scaleY = static_cast<double>(image->Height) / height;

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int origX = static_cast<int>(x * scaleX);
			int origY = static_cast<int>(y * scaleY);

			System::Drawing::Color color = image->GetPixel(origX, origY);
			scaledImage->SetPixel(x, y, color);
		}
	}

	return scaledImage;
}

System::Void BitmapConverter::Beastsy::SetupImage(System::Drawing::Image^ fileImage)
{
	ImagePreviewBox->Image = fileImage;

	if (fileImage->Size.Width < ImagePreviewHolder->Width)
	{
		System::Drawing::Bitmap^ originalImage = dynamic_cast<System::Drawing::Bitmap^>(fileImage);
		int targetWidth = ImagePreviewHolder->Width;
		int targetHeight = ImagePreviewHolder->Height;

		// Scale the zoomed image
		System::Drawing::Bitmap^ scaledImage = ScaleImage(originalImage, targetWidth, targetHeight);

		ImagePreviewBox->Image = scaledImage;
		// Adjust the picture box size to fit the scaled image
		ImagePreviewBox->Size = scaledImage->Size;
	}
}
