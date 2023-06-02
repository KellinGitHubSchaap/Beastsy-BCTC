#include "bitmap_converter.h"

void ConvertBitmap(String^ filename, const char* outputFilename)
{
    Bitmap ieks;

    String^ outputFolderPath = "output/";
    Directory::CreateDirectory(outputFolderPath);

    ieks.outfile = gcnew StreamWriter(outputFolderPath + gcnew String(outputFilename) + ".h");

    Bitmap^ bitmap = ReadBitmap(filename);
    bitmap->filename = gcnew String(outputFilename);

    ConvertBitmapToCArray(bitmap);
    ConvertPaletteToCArray(bitmap);

    Console::WriteLine("Bitmap converted to C array.");

    ieks.outfile->WriteLine("#endif // BITMAP_DATA_H");
    ieks.outfile->Close();

    delete[] bitmap->data;
}

Bitmap^ ReadBitmap(String^ filename)
{
    Bitmap^ bitmap = gcnew Bitmap();

    FileStream^ file = gcnew FileStream(gcnew String(filename), FileMode::Open, FileAccess::Read);

    // Read the bitmap header information
    file->Seek(18, SeekOrigin::Begin); // Skip the header to reach the width and height
    array<unsigned char>^ widthBytes = gcnew array<unsigned char>(4);
    array<unsigned char>^ heightBytes = gcnew array<unsigned char>(4);
    file->Read(widthBytes, 0, 4);
    file->Read(heightBytes, 0, 4);
    bitmap->width = BitConverter::ToInt32(widthBytes, 0);
    bitmap->height = BitConverter::ToInt32(heightBytes, 0);

    // Allocate memory for the pixel data
    bitmap->data = gcnew array<unsigned char>(bitmap->width * bitmap->height * 3);

    // Read the pixel data
    file->Seek(54, SeekOrigin::Begin); // Skip the header and color table
    file->Read(bitmap->data, 0, bitmap->width * bitmap->height * 3);

    file->Close();

    return bitmap;
}

void ConvertBitmapToCArray(Bitmap^ bitmap)
{
    Bitmap::outfile->WriteLine("#ifndef BITMAP_DATA_H");
    Bitmap::outfile->WriteLine("#define BITMAP_DATA_H\n");
    Bitmap::outfile->WriteLine("const unsigned int " + bitmap->filename + "MapData[] = {\t");

    int count = 0;
    for (int i = 0; i < bitmap->width * bitmap->height * 3; i += 3)
    {
        unsigned char r = bitmap->data[i + 2];
        unsigned char g = bitmap->data[i + 1];
        unsigned char b = bitmap->data[i];

        // Convert RGB to hex format
        Bitmap::outfile->Write("0x" + r.ToString("X2") + g.ToString("X2") + b.ToString("X2") + ", ");

        count++;
        if (count == 16)
        {
            Bitmap::outfile->WriteLine();
            Bitmap::outfile->Write("\t");
            count = 0;
        }
    }

    Bitmap::outfile->WriteLine();
    Bitmap::outfile->WriteLine("};\n");
}

void ConvertPaletteToCArray(Bitmap^ bitmap)
{
    List<String^>^ palette = gcnew List<String^>();
    Dictionary<String^, int>^ uniqueColors = gcnew Dictionary<String^, int>(); // Using Dictionary to store unique colors

    for (int i = 0; i < bitmap->width * bitmap->height * 3; i += 3)
    {
        unsigned char r = bitmap->data[i + 2];
        unsigned char g = bitmap->data[i + 1];
        unsigned char b = bitmap->data[i];

        // Convert RGB to hex format
        String^ hexValue = "0x" + r.ToString("X2") + g.ToString("X2") + b.ToString("X2");

        if (!uniqueColors->ContainsKey(hexValue)) // Check if color already exists in dictionary
        {
            uniqueColors->Add(hexValue, 0); // Add the color to the dictionary
        }
    }

    // Copy unique colors from dictionary keys to list
    for each (String ^ color in uniqueColors->Keys)
    {
        palette->Add(color);
    }

    WritePaletteToHeader(palette, bitmap->filename);
}

void WritePaletteToHeader(List<String^>^ palette, String^ filename)
{
    Bitmap::outfile->WriteLine("const unsigned int " + filename + "Palette[] = {");

    for each (String ^ color in palette)
    {
        Bitmap::outfile->Write(color + ", ");
    }

    Bitmap::outfile->WriteLine();
    Bitmap::outfile->WriteLine("};\n");
}