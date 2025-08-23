#include <cs50.h>
#include <stdio.h>

int main(void)
{
    string name_user =
        get_string("What's your name: \n"); // Getting name(string) from user with 'get_string'

    printf("hello, %s\n", name_user); // Printing 'name_user' name(string)

    return 0; // Finish program
}
// Mohammadreza_moktari_kia
