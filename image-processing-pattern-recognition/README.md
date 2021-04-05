# Image Processing and Pattern Recognition Lab (IT853)

## Questions

1. a) Write a program to show the minimum and the maximum pixel values of an 8 bits/pixel grayscale
   image. Also write a program to convert grayscale image to a binary image using threshold (Tth)
   operation where `Tth = (minimum pixel value + maximum pixel value) / 2`. Mathematically,
   `G(x, y) = 0 if f(x, y) ≤ (minimum gray value + maximum gray value) / 2; 1, otherwise`.

   b) Do the same thresholding operation considering `Tth = 128`.
   `G(x, y) = 0 if f(x, y) ≤ 128; 1 otherwise`.

   Highlight the differences in the two images obtained.

2. Write a program to implement down sampling of an image by a factor of 2. Apply the same effect
   for 2 / 3 successive times and comment on visual content. Finally, write a program to upscale
   the down sampled image through interpolation and comment on visual quality of the image.

3. Write a program to implement image negation operation

   `S = L - 1 - R`,

   `where R : pixel value of input image; S : pixel value of output image; L : maximum gray value`

   See the effect of the image negation operation for enhancing white or gray detail embedded in
   dark regions of an image dominant in size.

4. Write a program to implement change in dynamic range of an image from `[a, b]` to `[c, d]`. `a`
   and `c` are the minimum pixel values of input and output images respectively, while `b` and `d`
   are the maximum for the two. Comment on visual quality of the image after the operation.

5. Implement image negation operation using logical NOT operation and verify results with using
   linear transformation function.

6. Write a program to develop histogram of an image and show it through display. The size of the
   image and pixel values is made flexible. Show and comment about the effect on the histogram of
   the image if

   1. lower-order bit planes, and
   2. higher order bit plane are set to zero.

7. Write a program to implement histogram equalization of an 8-bit/pixel gray scale image. Show that
   a second pass of histogram equalization will produce exactly the same result as the first pass.

8. Write a Program to implement additive noise corruption of an image by manipulating `p%` randomly
   selected pixel values by an amount of `q%` (q may be fixed or random) for respective gray values.

9. Do the image averaging operation for `K = 8, 16, 32` number images (changing the value of `p` and
   `q`) and find the difference between the original and averaged image.

   Let `k` be `8`, generate `8` noisy images based on algorithm in assignment `8`, calculate average
   image, take sum of all `8` noisy images, then normalize using `8`, i.e. divide the summed image
   by `8` (summation and scalar division).

   Take the difference between the original (used in algorithm `8, f(x,y)`) and the averaged image.
   Plot the histogram of difference image.

   Repeat the steps for k=16, 32. Show the histogram in all cases.

   Observe the shifting in width and the mean position of the histogram of difference images. Plot
   the histogram of the difference image for all three cases.
