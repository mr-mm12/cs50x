#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{ // Creat variables
    int R_M, G_M, B_M;
    float G_out;

    for (int i = 0; i < height; i++) // Move on image height
    {
        for (int j = 0; j < width; j++) // Move on image width
        {
            R_M = image[i][j].rgbtRed;   // red_main(R_M) = Pixel 'i' and 'j'
            G_M = image[i][j].rgbtGreen; // green_main(G_M) = Pixel 'i' and 'j'
            B_M = image[i][j].rgbtBlue;  // blue_main(B_M) = Pixel 'i' and 'j'

            G_out = round((R_M + G_M + B_M) / 3.0); // Finding the average pixel color

            // Create an image with new pixels
            image[i][j].rgbtRed = G_out;
            image[i][j].rgbtGreen = G_out;
            image[i][j].rgbtBlue = G_out;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // Creat variables
    int originalRed, originalGreen, originalBlue;
    int sepiaRed, sepiaGreen, sepiaBlue;

    for (int i = 0; i < height; i++) // Move on image height
    {
        for (int j = 0; j < width; j++) // Move on image width
        {
            originalRed = image[i][j].rgbtRed;     // red_main(R_M) = Pixel 'i' and 'j'
            originalGreen = image[i][j].rgbtGreen; // green_main(G_M) = Pixel 'i' and 'j'
            originalBlue = image[i][j].rgbtBlue;   // blue_main(B_M) = Pixel 'i' and 'j'

            // Sepia Romulans
            float sepiaRedF =
                .393 * originalRed + .769 * originalGreen + .189 * originalBlue; // for red
            float sepiaGreenF =
                .349 * originalRed + .686 * originalGreen + .168 * originalBlue; // for green
            float sepiaBlueF =
                .272 * originalRed + .534 * originalGreen + .131 * originalBlue; // for blue

            // As a precaution, if the number becomes
            // larger than 255 when rounding numbers
            // Limit to 255
            if (sepiaRedF > 255)
                sepiaRedF = 255;
            if (sepiaGreenF > 255)
                sepiaGreenF = 255;
            if (sepiaBlueF > 255)
                sepiaBlueF = 255;

            // Place in image with round
            image[i][j].rgbtRed = (int) round(sepiaRedF);
            image[i][j].rgbtGreen = (int) round(sepiaGreenF);
            image[i][j].rgbtBlue = (int) round(sepiaBlueF);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE RP[width];

    for (int i = 0; i < height; i++) // Move on image height
    {
        for (int j = 0; j < width; j++) // Move on image width
        {
            RP[j] = image[i][j]; // Saves a copy of row i of the
            // image into the RP array
        }
        for (int k = 0; k < width; k++) // Move on image width
        {
            // Replace the red color value of pixel [i][k]
            // with its symmetrical pixel from the
            // right (horizontally inverted)
            image[i][k].rgbtRed = RP[width - k - 1].rgbtRed;
            image[i][k].rgbtGreen = RP[width - k - 1].rgbtGreen;
            image[i][k].rgbtBlue = RP[width - k - 1].rgbtBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Copy array to store the original version of the image
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    // Copy the entire image into the copy array
    {
        for (int j = 0; j < width; j++)
        {
            // Pixel (i, j) from the original image is copied into the copy
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    // Scroll the pixels of the original image
    {
        for (int j = 0; j < width; j++)
        {
            int c = 0;
            float r_sum = 0; // sum of red color values
            float g_sum = 0; // sum of green color values
            float b_sum = 0; // sum of blue color values

            for (int k = -1; k < 2; k++)
            // Check neighbors in a 3x3 area around pixel (i, j)
            {
                for (int l = -1; l < 2; l++) // Horizontal movement
                {
                    if (!(i + k < 0 || i + k >= height || j + l < 0 || j + l >= width))
                    // Condition: Pixel is not outside the image boundary
                    {
                        // Add the color values of neighboring pixels to the sum
                        r_sum += copy[i + k][j + l].rgbtRed;
                        g_sum += copy[i + k][j + l].rgbtGreen;
                        b_sum += copy[i + k][j + l].rgbtBlue;
                        c++; // Increment the counter
                    }
                    else
                    {
                        continue; // If out of bounds, continue
                    }
                }
            }
            // Calculate the average of the colors and
            // replace them in the original image
            image[i][j].rgbtRed = (int) round(r_sum / c);
            image[i][j].rgbtGreen = (int) round(g_sum / c);
            image[i][j].rgbtBlue = (int) round(b_sum / c);
        }
    }
    return;
}

// Mohammadreza_mokhtari_kia
