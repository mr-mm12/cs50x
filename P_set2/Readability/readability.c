#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string txt = get_string("Text: \n"); // Getting text from user

    int letters = 0, words = 1, sentences = 0;   // Creating variables
    for (int i = 0, m = strlen(txt); i < m; i++) // Check what is text?
    {
        if (isalpha(txt[i])) // If the text character was a letter
        {
            letters++; // Add to the letters
        }
        else if (txt[i] == '.' || txt[i] == '?' ||
                 txt[i] == '!') // If the text character is a symbol
        {
            sentences++; // Add to the sentences
        }
        else if (txt[i] == ' ') // If the text characters are words
        {
            words++; // Add to the words
        }
    }

    float l =
        ((float) letters / words) * 100; // Finding the average number of
                                         // letters in 100 words(I use float to be more precise)
    float s = ((float) sentences / words) *
              100; // Finding the average number of
                   // sentences per 100 words(I use float to be more precise)

    float index = 0.0588 * l - 0.296 * s - 15.8; // Finding the Reading Difficulty Index

    int g = round(index); // Rounding an index using 'round' in the ''math.h' library
    if (g < 1)            // if grade smaller than 1
    {
        printf("Before Grade 1\n"); // print this --> "Before Grade 1"
        return 0;                   // Successful :)
    }
    else if (g >= 16) // if grade biger than 16 or == 16
    {
        printf("Grade 16+\n"); // print this --> "Grade 16+" "
        return 0;              // Successful :)
    }
    else // Otherwise
    {
        printf("Grade %i\n", g); // print this --> "Grade {grade}"
        return 0;                // Successful :)
    }
}
// Mohammadreza_mokhtari_kia
