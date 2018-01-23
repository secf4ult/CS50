#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: resize infile outfile\n");
        return 1;
    }

    // parse float input
    float factor = atof(argv[1]);
    if (factor <= 0 || factor > 100)
    {
        fprintf(stderr, "factor must be a float value in (0.0, 100]\n");
        return 2;
    }

    // remember file names
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file
    FILE *inptr = fopen(infile, "r");
    if (infile == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not open %s.\n", infile);
        return 5;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(outptr);
        fprintf(stderr, "Could not create %s.\n", infile);
        return 6;
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

    // save the old biWidth and biHeight
    LONG old_biWidth = bi.biWidth;
    LONG old_biHeight = bi.biHeight;

    // update the BITMAPINFOHEADER
    bi.biWidth *= factor;
    bi.biHeight *= factor;

    // determine padding for scanlines
    int old_padding = (4 - (old_biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int new_padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + new_padding) * abs(bi.biHeight);

    // update the BITMAPFILEHEADER
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);


    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // when f is a value in [1.0, 100]
    // for each row
    if (factor >= 1)
    {
        for (int i = 0, height = abs(old_biHeight); i < height; i++)
        {
            // for n times
            for (int n = 0; n < factor; n++)
            {
                // for each pixel in source bmp
                for (int j = 0; j < old_biWidth; j++)
                {
                    // temporary storage
                    RGBTRIPLE triple;

                    // read RGB triple from infile
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                    // write RGB triple to outfile for n times, horizontally
                    for (int k = 0; k < factor; k++)
                    {
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    }
                }

                // then add new_padding in outfile
                for (int k = 0; k < new_padding; k++)
                {
                    fputc(0x00, outptr);
                }

                // cursor back to the row head
                fseek(inptr, -old_biWidth * sizeof(RGBTRIPLE), SEEK_CUR);
            }

            // skip the line because the cursor back to the row head
            fseek(inptr, old_biWidth * sizeof(RGBTRIPLE) + old_padding, SEEK_CUR);
        }
    }
    // when factor is a value in (0.0, 1.0)
    else
    {
        for (int i = 0, height = abs(old_biHeight); i < height; i++)
        {
            if ( ceil(i * factor) != ceil((i + 1) * factor) )
            {
                // iterate over each pixel in the width of the infile (original file)
                for (int j = 0; j < bi.biWidth; j++)
                {
                    // same as above, but now considering horizontal iteration count
                    if (ceil(j * factor) != ceil((j + 1) * factor))
                    {
                        // temporary storage for triple
                        RGBTRIPLE triple;

                        // read one pixel (aka 1 RGBTRIPLE) from the infile
                        fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                        // write one pixel to the outfile
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                    }
                    else
                    {
                        // skip over 1 pixel
                        fseek(inptr, sizeof(RGBTRIPLE), SEEK_CUR);
                    }
                }

                // skip over the padding in the infile
                fseek(inptr, old_padding, SEEK_CUR);

                // add it back to the outfile
                for (int k = 0; k < new_padding; k++)
                {
                    fputc(0x00, outptr); // each byte of padding consists of 2 zero's, in hex
                }
            }
            else
            {
                // skip over 1 horizontal line
                // line size in bytes is the product of amount of pixels times size of each pixel (3 or size of RGBTRIPLE)
                // finally add padding, if any exists in the original file
                fseek(inptr, (sizeof(RGBTRIPLE) * abs(bi.biWidth) + old_padding), SEEK_CUR);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}