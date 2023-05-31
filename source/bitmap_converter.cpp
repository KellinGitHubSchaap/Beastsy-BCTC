#include "../include/bitmap_converter.hpp"

std::ofstream outfile;

void ConvertBitmap(const char *filename, const char* outputFilename)
{
    std::string outputFolderPath = "output/";
    std::filesystem::create_directory(outputFolderPath);

    outfile.open(outputFolderPath + std::string(outputFilename) + ".h");

    Bitmap bitmap = ReadBitmap(filename);
    bitmap.filename = std::string(outputFilename);

    ConvertBitmapToCArray(bitmap);
    ConvertPaletteToCArray(bitmap);

    std::cout << "Bitmap converted to C array.\n";

    outfile << "#endif // BITMAP_DATA_H\n";
    outfile.close();

    delete[] bitmap.data;
}

Bitmap ReadBitmap(const char *filename)
{
    Bitmap bitmap;

    std::ifstream file(std::string(filename) + ".bmp", std::ios::binary);

    // Read the bitmap header information
    file.seekg(18, std::ios::beg); // Skip the header to reach the width and height
    file.read(reinterpret_cast<char *>(&bitmap.width), sizeof(bitmap.width));
    file.read(reinterpret_cast<char *>(&bitmap.height), sizeof(bitmap.height));

    // Allocate memory for the pixel data
    bitmap.data = new unsigned char[bitmap.width * bitmap.height * 3];

    // Read the pixel data
    file.seekg(54, std::ios::beg); // Skip the header and color table
    file.read(reinterpret_cast<char *>(bitmap.data), bitmap.width * bitmap.height * 3);

    file.close();

    return bitmap;
}

void ConvertBitmapToCArray(const Bitmap &bitmap)
{
    outfile << "#ifndef BITMAP_DATA_H\n";
    outfile << "#define BITMAP_DATA_H\n\n";
    outfile << "const unsigned int " + bitmap.filename + "MapData[] = {\n\t";

    int count = 0;
    for (int i = 0; i < bitmap.width * bitmap.height * 3; i += 3)
    {
        unsigned char r = bitmap.data[i + 2];
        unsigned char g = bitmap.data[i + 1];
        unsigned char b = bitmap.data[i];

        // Convert RGB to hex format
        outfile << "0x" << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(r);
        outfile << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(g);
        outfile << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(b) << ", ";

        count++;
        if (count == 16)
        {
            outfile << "\n\t";
            count = 0;
        }
    }

    outfile << "\n};\n\n";
}

void ConvertPaletteToCArray(const Bitmap& bitmap)
{
    std::vector<std::string> palette;
    std::set<std::string> uniqueColors;

    for (int i = 0; i < bitmap.width * bitmap.height * 3; i += 3)
    {
        unsigned char r = bitmap.data[i + 2];
        unsigned char g = bitmap.data[i + 1];
        unsigned char b = bitmap.data[i];

        // Convert RGB to hex format
        std::stringstream hexValue;
        hexValue << "0x" << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(r);
        hexValue << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(g);
        hexValue << std::setw(2) << std::setfill('0') << std::hex << static_cast<int>(b);

        uniqueColors.insert(hexValue.str());
    }

    std::copy(uniqueColors.begin(), uniqueColors.end(), std::back_inserter(palette));
    WritePaletteToHeader(palette, bitmap.filename);
}

void WritePaletteToHeader(const std::vector<std::string>& palette, const std::string& filename)
{
    outfile << "const unsigned int " + filename + "Palette[] = {\n\t";

    for(const auto& color : palette)
    {
        outfile << color << ", ";
    }

    outfile << "\n};\n\n";
}