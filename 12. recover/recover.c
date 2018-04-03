/**
 * recover.c
 *
 * Recovers jpg images from raw data.
 *
 * Najib el Moussaoui
 * Programming I
 * Pset 4: forensics
 * Minor Programming
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover infile\n");
        return 1;
    }

    // take file from command line
    char *infile = argv[1];

    // open file
    FILE *file = fopen(infile, "r");

    // check is file can be opened
    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // initialize a buffer for to write to
    unsigned char buffer[512];

    // initialize an array for the file name
    char filename[8];


    int jpg_counter = 0;

    // initialise img file
    FILE *img;

    // boolean checks for proper control
    bool notfirst = false;
    bool to_write = false;

    // read into raw data until no more blocks of 512 bytes left
    while ((fread(&buffer, 512, 1, file)) == 1)
    {
        // check for header
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // close every previous image, after the first
            if (notfirst)
            {
                fclose(img);
            }

            notfirst = true;

            // create a jpg file, open it and increment the count of files
            sprintf(filename, "%03i.jpg", jpg_counter);
            jpg_counter++;
            img = fopen(filename, "w");

            // start writing all blocks
            to_write = true;
            fwrite(&buffer, 512, 1, img);
        }
        else if (to_write)
        {
            fwrite(&buffer, 512, 1, img);
        }
    }

    // close last img and raw file
    fclose(img);
    fclose(file);
}