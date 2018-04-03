/**
 * resize.c
 *
 * Najib el Moussaoui
 * Pset 4: forensics
 * Programming I
 * Minor Programming
 */

#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize f infile outfile\n");
        return 1;
    }

    // ensure resize factor is > 0 and < 100
    if (!(atof(argv[1]) <= 100))
    {
        fprintf(stderr, "Usage: enter resize factor between 0 and 100\n");
        return 1;
    }

    // convert resize factor from type string to type float
    float f = atof(argv[1]);

    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // determine padding for scanlines (old image)
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // intialize a 2D array grid to store old image in
    RGBTRIPLE storage[bi.biWidth][abs(bi.biHeight)];

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // iterate over pixels in scanline
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // store all pixels of old image in a 2D array
            storage[j][i] = triple;
        }

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);
    }

    // change height and width of the resized image by resize factor f
    bi.biHeight *= f;
    bi.biWidth *= f;

    // recalculate padding after adjusting height and width
    int new_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // calculate how long a scanline is in bytes
    int new_scanline = bi.biWidth * sizeof(RGBTRIPLE) + new_padding;

    // update header info after scaling
    bi.biSizeImage = new_scanline * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // new indices for resized image array
    int new_j;
    int new_i;

    // loop over new scanline and height over image and write to outfile
    for (int i = 0, height = abs(bi.biHeight); i < height; i++)
    {
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // calculate new indices of the resized array
            // divide by scale factor to get a smaller or bigger array for image
            new_j = j / f;
            new_i = i / f;

            // resize the original pixel array and write in RGB triple
            triple = storage[new_j][new_i];

            // write RGB triple to outfile
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);

        }

        // add the padding back at the end of each scanline
        for (int k = 0; k < new_padding; k++)
        {
            fputc(0x00, outptr);
        }
    }


    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
