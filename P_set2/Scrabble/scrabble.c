#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    int points[] = {// Specifying points for each letter
                    1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

    int v_num[2] = {0, 0}; // Create a variable to sum the points of two players
    for (int pla = 0; pla < 2; pla++)
    // Gives a number and score for each character in the input
    {
        string let = get_string("Player %d: \n", pla + 1); // From players every time they enter
        for (int i = 0, n = strlen(let); i < n; i++) // Convert one character to uppercase each time
        {
            let[i] = toupper(let[i]); // Convert one character to uppercase
        }
        for (int i = 0; i < strlen(let);
             i++) // 'i' starts at zero and continues to the length of the string (strlen(let))
        {
            if (isalpha(let[i])) // If it were a letter
            {
                char letters = let[i]; // Create a new variable of type 'charecter' named 'letters'
                int index = toupper(letters) - 'A'; // Calculating the index of each letter
                int value = points[index];          // Find in 'points'
                v_num[pla] += value;                // Accumulate points in variable 'v_num'
            }
        }
    }
    if (v_num[0] > v_num[1]) // if score player 1 > score player 2
    {
        printf("player 1 wins!\n"); // player 1 wins
        return 0;                   // Successful :)
    }
    else if (v_num[0] < v_num[1]) // if score player 1 < score player 2
    {
        printf("player 2 wins!\n"); // player 2 wins
        return 0;                   // Successful :)
    }
    else if (v_num[0] == v_num[1]) // if score player 1 = score player 2
    {
        printf("Tie!\n"); // player 1 tie with player 2
        return 0;         // Successful :)
    }
    else // To be sure
    {
        return 1; // not successful :(
    }
}
// Mohammadreza_mokhtari_kia
