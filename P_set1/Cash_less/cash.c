#include <cs50.h>
#include <stdio.h>

int main(void)
{
    while (true)
    {
        int num_cent = get_int("Change owed: \n"); // Getting Change owed from user to change it.

        if (num_cent >= 0) // If the number is greater than 0, it continues.
        {
            int R_25 = num_cent % 25; // Finding how many 25s are in it.
            int A_25 = num_cent / 25;

            int R_10 = R_25 % 10; // Finding how many 10s are in it.
            int A_10 = R_25 / 10;

            int R_5 = R_10 % 5; // Finding how many 5s are in it.
            int A_5 = R_10 / 5;

            int R_1 = R_5 % 1; // Finding how many 1s are in it.
            int A_1 = R_5 / 1;

            int ANS = A_25 + A_10 + A_5 +
                      A_1; // Finding how many coins he should give to get the smallest amount.
            printf("%d\n", ANS); // printing answer.

            break;    // finish
            return 0; // Successful
        }
    }
}
// Mohammadreza_mokhtari_kia
