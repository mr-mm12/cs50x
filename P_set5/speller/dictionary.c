// Some parts of this code were provided by the CS50 team (Distribution Code).
// This code was completed and developed by me for practicing Inheritance.
// Some parts were learned from internet(https://www.aparat.com/v/d41os53)

// Implements a dictionary's functionality

#include "dictionary.h"
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// Choose number of buckets in hash table
const unsigned int N = 200003;

// Hash table
node *table[N];

int ds = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int hv = hash(word);
    node *n = table[hv];

    while (n != NULL)
    // strcasecmp (actually it should be strcasecmp)
    // compares two strings without regard to uppercase or
    // lowercase letters.
    {
        if (strcasecmp(word, n->word) == 0)
        {
            return true;
        }
        n = n->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // Improve this hash function
    unsigned int s = 0;
    int light = 300000;       // Speed of light
    int year_Einstein = 1879; // Albert's birthday
    int my_birthday = 2010;   // My birthday
    int p_BTC = 113000;       // Bitcoin price in 2025
    int M = round(year_Einstein * light + my_birthday / p_BTC) / 1000;
    for (int w = 0; word[w] != '\0'; w++)
    // As long as it is not at the end of the word
    {
        s = (s * M + tolower(word[w])) % N; // Sum of ASCII codes of letters
    }
    return s;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dp = fopen(dictionary, "r");
    if (dictionary == NULL)
    {
        printf("Unable to open %s\n", dictionary);
        return false;
    }
    char nw[LENGTH + 1];
    while (fscanf(dp, "%s", nw) != EOF) // EOF = End Of File
    {
        node *m = malloc(sizeof(node));
        if (m == NULL)
        {
            return false;
        }
        strcpy(m->word, nw);
        int hv = hash(nw);
        m->next = table[hv];
        table[hv] = m;
        ds++;
    }
    fclose(dp);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{

    return ds;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *n = table[i];
        while (n != NULL)
        {
            node *t = n;
            n = n->next;
            free(t);
        }
        if (n == NULL && i == N - 1)
        {
            return true;
        }
    }
    return false;
}

// Mohammadreza_mokhtari_kia
