// Some parts of this code were learned with the help of this video:
// https://www.aparat.com/v/g814cfk

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2) // Getting two 'argc' from the user
    {
        printf("Usage: ./recover FILE\n"); // Otherwise print
        // this --> "Usage: ./recover FILE"
        return 1; // Exit with error code
    }

    FILE *d = fopen(argv[1], "r"); // Open the input file (e.g. card.raw) for reading
    if (d == NULL)
    // If the file cannot be opened
    {
        printf("Could not open file.\n");
        return 1; // Exit with error code
    }
    // Create a 512-byte buffer on
    // the heap to store the read data
    unsigned char *t = malloc(512);

    if (t == NULL) // If there was not enough memory
    {
        return 1; // Exit with error code
    }
    // An array of output file
    // names (e.g. 000.jpg → 001.jpg → ...)
    char filename[8];
    int im = 0;        // Counter of images
    FILE *imgf = NULL; // Pointer to the current image file (initially empty)

    while (fread(t, 1, 512, d) == 512)
    // until we read exactly 512 bytes from the input file (block by block)
    {
        if (t[0] == 0xff && t[1] == 0xd8 && t[2] == 0xff && (t[3] & 0xf0) == 0xe0)
        // Check if the current block is the start of a new JPG file or not
        {
            if (imgf != NULL)
            // If an image is already open, close it first.
            {
                fclose(imgf);
            }
            // Generate new file names like 000.jpg, 001.jpg, ...
            sprintf(filename, "%03i.jpg", im);
            // Open a new file for writing
            imgf = fopen(filename, "w");
            // Increment the photo counter
            im++;
        }
        if (imgf != NULL)
        // If an image file is currently
        // open, write this block into it
        {
            fwrite(t, 1, 512, imgf);
        }
    }
    if (imgf != NULL)
    // After the loop finishes,
    // if there is still a file open, close it
    {
        fclose(imgf);
    }
    // Free the memory we got with malloc
    free(t);
    // Close the main input file
    fclose(d);

    return 0; // Successful completion
}

// Mohammadreza_mokhtari_kia
