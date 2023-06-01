UPDATE LOG - Bitmap Converter To C (BCTC):

--- : Initial Release : ---
5/31/2023 : v1.0.0
1. User is able to write down the input path of their .bmp file
2. User is able to write down the output name of their .h file
3. Converter automatically saperates the color (palette) from the data
4. Converter automatically makes an "output" folder if none is present
5. Converter can currently convert an image with a Bitdepth of 3 bytes = 8 bits per RGB channel = 24 bits per pixel
6. Converter isnt leaking memory so it is safe for multiple uses

Issues / Bugs
1. Converter can't convert to GBA values = 2 bytes = 5 bits per RGB channel = 15 bits per pixel
2. Converter is missing a UI for a more user friendly experience
3. Converter might not be fully optimized when trying to convert really big .bmp files with a lot of colors

To Do List:
- Visualise the converter instead of it being code/makefile based
- .bmp converting for the GBA should be made possible