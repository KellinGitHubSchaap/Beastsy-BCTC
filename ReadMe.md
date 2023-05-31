<p>
Because I am making a framework project in C++, I needed to make sure that I was able to create bitmaps and be able to use them inside of my environment.
And since I don't like to convert .bmp's on sketchy websites, of which I don't know what data I'll get when converting, I quickly wrote my own converter that will handle this for you (and me =P).

What do you need to do!
1. Make sure that G++ compiler is installed on your PC (and possibly have MSYS2 or any other terminal)
2. Make sure that the MakeFile is in the `root` of your project as it will scan from there.
3. (For now) the MakeFile will remain working as long as you don't add really strange headers or libraries to your project, as it wasnt meant to compile that.
4. Open the main.cpp file and fill in main the following function call -> `ConvertBitmap(const char* filename, const char* outputFilename)`
place the file path of your .bmp file into the first parameter starting from the `root` of your project and in the secondParameter you'd want to give the output name of your converted .bmp file.

Here is an example:
</p>

`
#include "../include/bitmap_converter"

int main()
{
	ConvertBitmap("assets/smiley", "differentSmiley");
	return 0;
}
`
