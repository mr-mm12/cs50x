#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    // Loop over all candidates
    {
        if (strcmp(candidates[i].name, name) == 0)
        // Exact comparison of candidate name with name entered by voter
        // strcmp returns 0 when two strings are exactly equal
        {
            candidates[i].votes++; // If the name is found, the number
                                   // of votes for that candidate is +1
            return true;           // The vote was valid, return true
        }
    }
    // If no candidate with the entered name is found,
    // return false (invalid vote)
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int max_votes = 0; // A variable to store the highest number of votes

    for (int i = 0; i < candidate_count; i++)
    // Step 1: Find the highest number of votes among all candidates
    {
        if (candidates[i].votes > max_votes)
        // If the current candidate's votes are more than max_votes
        {
            max_votes = candidates[i].votes; // Update max_votes to this new value
        }
    }

    for (int i = 0; i < candidate_count; i++)
    // Step 2: Print all candidates with the same number of votes as the highest number of votes
    // This is done to cover the tie condition
    {
        if (candidates[i].votes == max_votes)
        // If the number of votes for the candidate was equal to the highest number of votes
        {
            printf("%s\n", candidates[i].name); // Print the winning candidate
        }
    }
}
// Mohammadreza_mokhtari_kia
