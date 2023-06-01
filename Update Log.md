# UPDATE LOG - Bitmap Converter To C (BCTC):

--- : Initial Release : --- <br>
5/31/2023 : v1.0.0
1. User is able to write down the input path of their .bmp file
2. User is able to write down the output name of their .h file
3. Converter automatically saperates the color (palette) from the data
4. Converter automatically makes an "output" folder if none is present
5. Converter can currently convert an image with a Bitdepth of 3 bytes = 8 bits per RGB channel = 24 bits per pixel
6. Converter isnt leaking memory so it is safe for multiple uses

--- : Visualizing Conversion : --- <br>
6/1/2023 : V2.0.0
1. The user can now convert their .bmp file inside of an actual application instead of using some coding magic.
2. The user can pick a very small image (16x16 pixels) and see it upscaled in the canvas (500x500 pixels).
3. The user can pick a very big image (1920x1080 pixels) and be allowed to pan over the image.

--- : Quick Fix Round : --- <br>
6/1/2023 : V2.0.1
1. When the user hits `Convert` the file will be outputted at the users Desktop (will be changed).
2. File export will now grab the name of the .bmp file selected and will be used as exported name file with .h added.

## To Do List
- ~~Visualise the converter instead of it being code/makefile based
- .bmp converting for the GBA should be made possible
- Make sure that the output location can be decided on by the user
- Make the user be able to select a palette color that will become a transparent color
- Make the user be able to see all the colors used within the .bmp image

## Issues / Bugs
1. Converter can't convert to GBA values = 2 bytes = 5 bits per RGB channel = 15 bits per pixel
2. ~~Converter is missing a UI for a more user friendly experience
3. ~~Converter might not be fully optimized when trying to convert really big .bmp files with a lot of colors
