// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float f = atof(argv[3]);

    // Copy WAV header
    uint8_t header[HEADER_SIZE];                          // Array to store header bytes
    fread(header, sizeof(uint8_t), HEADER_SIZE, input);   // Read 44 bytes from input
    fwrite(header, sizeof(uint8_t), HEADER_SIZE, output); // Write 44 bytes to output

    // Read samples, adjust volume, and write to output
    int16_t s;
    while (fread(&s, sizeof(int16_t), 1, input)) // Read one sample
    {
        int t = s * f; // Scale sample by factor
        // Limit value to prevent overflow/clipping
        if (t > 32767)
            t = 32767;
        if (t < -32768)
            t = -32768;

        s = t;
        fwrite(&s, sizeof(int16_t), 1, output); // Write adjusted sample
    }

    // Close files
    fclose(input);
    fclose(output);
}

// Mohammadreza_mokhtari_kia
