#include <cs50.h>
#include <stdbool.h>
#include <stdio.h>

int main(void)
{
    int height; // To access the 'for' rings

    while (true)
    {
        height = get_int("Height: \n"); // Getting a number(Hight number) from user
        if (height > 0)                 // Checks if the number is positive. (height > 0)
        {
            break; // means user enter the +number.
        }
    }

    // Building a Mario Pyramid with height of 'height'
    for (int i = 1; height + 1 > i;
         i++) // As long as 'i' is smaller than 'height + 1', Increase 'i'
    {
        for (int j = 0; j < height - i;
             j++) // As long as 'j' is smaller than 'height - i', Increase 'j'
        {
            printf(" "); // Print space
        }

        for (int k = 0; k < i; k++) // As long as 'K' is smaller than 'i', Increase 'k'
        {
            printf("#"); // Print '#'
        }

        printf("\n"); // Go to the next line
    }
}
// Mohammadreza_moktari_kia
