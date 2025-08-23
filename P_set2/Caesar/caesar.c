#include <cs50.h>   // For get_string, string
#include <ctype.h>  // For isupper, islower, isdigit
#include <stdio.h>  // for printf
#include <stdlib.h> // for atoi
#include <string.h> // for strlen

int main(int argc, string argv[]) // start...
{
    if (argc != 2) // Checks if it has 2 arguments, Otherwise
    {
        printf("Usage: ./caesar key\n"); // print this --> "Usage: ./caesar key"
        return 1;                        // Not Successful
    }
    for (int m = 0; m < strlen(argv[1]);
         m++) // Checks whether the second argument is a number, otherwise the program ends
    {
        if (!isdigit(argv[1][m])) // If there were no numbers
        {
            printf("Usage: ./caesar key\n"); // print this --> "Usage: ./caesar key"
            return 1;                        // Not Successful
        }
    }
    int key = atoi(argv[1]);                  // Convert string to intiger
    string txt = get_string("plaintext: \n"); // Getting plaintext from user

    printf("ciphertext: "); // print this --> "ciphertext: "

    for (int i = 0; i < strlen(txt); i++) // Encrypts each letter of the input text.
    {
        char c = txt[i]; // Convert letters to characters

        if (isupper(c)) // If the letters were capitalized
        {
            printf("%c", (c - 'A' + key) % 26 + 'A'); // print this --> {That word}
        }
        else if (islower(c)) // If the letters were lowercase
        {
            printf("%c", (c - 'a' + key) % 26 + 'a'); // print this --> {That word}
        }
        else // Otherwise
        {
            printf("%c", c); // If it is not among the letters, it prints itself.
        }
    }
    printf("\n"); // Go to the next line
}
// Mohammadreza_mokhtari_kia
