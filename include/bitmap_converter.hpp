#ifndef BITMAP_CONVERTER_HPP
#define BITMAP_CONVERTER_HPP

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <set>
#include <filesystem>

struct Bitmap
{
    int width;
    int height;
    unsigned char *data;
    std::string filename;
};

extern std::ofstream outfile;

void ConvertBitmap(const char *filename, const char* outputFilename);
Bitmap ReadBitmap(const char *filename);
void ConvertBitmapToCArray(const Bitmap &bitmap);
void ConvertPaletteToCArray(const Bitmap &bitmap);
void WritePaletteToHeader(const std::vector<std::string>& palette, const std::string& filename);

#endif // BITMAP_CONVERTER_HPP
