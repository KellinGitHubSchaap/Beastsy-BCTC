#pragma once
#ifndef BITMAP_CONVERTER_H
#define BITMAP_CONVERTER_H

using namespace System;
using namespace System::IO;
using namespace System::Collections::Generic;

public ref struct Bitmap
{
    int width;
    int height;
    array<unsigned char>^ data;
    String^ filename;
    static StreamWriter^ outfile;
};

void ConvertBitmap(String^ filename, String^ outputFilePath, String^ outputFilename);
Bitmap^ ReadBitmap(String^ filename);
void ConvertBitmapToCArray(Bitmap^ bitmap);
void ConvertPaletteToCArray(Bitmap^ bitmap);
void WritePaletteToHeader(List<String^>^ palette, String^ filename);

#endif // !BITMAP_CONVERTER_H
