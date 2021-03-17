# Assignment 1: Image Thresholding

## Questions

1. a) Write a program to show the minimum and the maximum pixel values of an 8 bits/pixel grayscale
   image. Also write a program to convert grayscale image to a binary image using threshold (Tth)
   operation where Tth = (minimum pixel value + maximum pixel value) / 2. Mathematically, G(x, y) = 0
   if f(x, y) ≤ (minimum gray value + maximum gray value) / 2; 1, otherwise.

    b) Do the same thresholding operation considering Tth = 128. G(x, y) = 0 if f(x, y) ≤ 128; 1
    otherwise.

    Highlight the differences in the two images obtained.

2. Write a program to implement down sampling of an image by a factor of 2. Apply the same effect
   for 2 / 3 successive times and comment on visual content. Finally, write a program to upscale the down
   sampled image through interpolation and comment on visual quality of the image.
