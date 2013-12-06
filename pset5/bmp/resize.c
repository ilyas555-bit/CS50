/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Copies a BMP piece by piece, just because.
 *
 * Lucy Nam
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"
#define METADATA 54

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy factor infile outfile\n");
        return 1;
    }

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    int n = atoi(argv[1]); 
    
    // ensures that n is [1, 100]
    if ((n < 1) || (n > 100))
    {
        return 0;
    }
    
    // open input file 
    FILE* inptr = fopen(infile, "r");
    
    // checks if input file is NULL
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    
    // checks if output file is NULL
    if (outptr == NULL)
    {
        // closes input file
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
    
    // determine padding per line for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int newpadding = (padding * n) % 4;
    bf.bfSize = (bf.bfSize - METADATA - padding * abs(bi.biHeight)) 
    * n * n + METADATA + newpadding * abs(bi.biHeight) * n;
    
    // change bi.biSizeImage to new bi.biSizeImage
    bi.biSizeImage = (bi.biSizeImage - padding * abs(bi.biHeight)) 
    * n * n + newpadding * abs(bi.biHeight) * n; 
    
    // change bi.biHeight to new bi.biHeight
    bi.biHeight = bi.biHeight * n; 
    
    // change bi.biWidth to new bi.biWidth
    bi.biWidth = bi.biWidth * n; 
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
       
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight / n); i < biHeight; i++)
    {
        // repeat the line n times
        for (int lines = 0; lines < n; lines++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth / n; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                // copies the pixel in the same line n times
                for (int k = 0; k < n; k++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
             }
        
            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);

            // then add it back (to demonstrate how)
            for (int k = 0; k < newpadding; k++)
            {
                fputc(0x00, outptr);
            }
        
            // goes to front of the line
            if (lines != (n - 1))
            {
                fseek(inptr, -bi.biWidth / n * sizeof(RGBTRIPLE) 
                - padding, SEEK_CUR); 
            }  
            }      
        }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
