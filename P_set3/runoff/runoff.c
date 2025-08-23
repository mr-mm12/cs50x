#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        // // The name matched
        {
            preferences[voter][rank] = i; // voter rank for this candidate
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int i = 0; i < voter_count; i++)
    // for all voters
    {
        for (int j = 0; j < candidate_count; j++)
        // for all their ranks
        {
            int candidate_index = preferences[i][j];
            // If this candidate is not removed, the vote goes to him/her
            if (!candidates[candidate_index].eliminated)
            {
                candidates[candidate_index].votes++;
                break; // Only one vote is given to the first available option
            }
        }
    }
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int majority = voter_count / 2; // More than half of the votes
    for (int i = 0; i < candidate_count; i++)
    // It repeats on all candidates
    {
        if (!candidates[i].eliminated && candidates[i].votes > majority)
        // Checks whether:
        // The candidate has been eliminated and the number of votes is
        // more than half of the number of voters
        {
            printf("%s\n",
                   candidates[i].name); // If the above condition is
                                        // correct, the candidate's name
                                        // will be published, meaning the winner will be declared
            return true; // The print_winner() function says: "A winner has been found" and
                         // the rest of the loop stops executing.
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int min = -1; // Initial value for lowest vote, -1 means no candidate
                  // has been reviewed yet
    for (int i = 0; i < candidate_count; i++)
    // Loop over all candidates
    {
        if (!candidates[i].eliminated)
        // Only candidates that have not been deleted are checked
        {
            if (min == -1 || candidates[i].votes < min)
            // If min has not been determined yet or this candidate's
            // vote is less than min
            {
                min = candidates[i].votes; // // The lowest vote is updated
            }
        }
    }
    return min; // The lowest number of votes among the remaining candidates is returned
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    for (int i = 0; i < candidate_count; i++)
    // For all candidates
    {
        if (!candidates[i].eliminated)
        // Only non-deleted candidates are checked
        {
            if (candidates[i].votes != min)
            // If this candidate's vote is different
            // from the min, it is not a tie
            {
                return false; // not a tie
            }
        }
    }
    return true; // If all are equal to min, it is a tie
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)
    // Loop over all candidates
    {
        if (!candidates[i].eliminated)
        // Only candidates that have not been deleted are checked
        {
            if (candidates[i].votes == min)
            // If the candidate's number of votes is
            // equal to the lowest number of votes
            {
                candidates[i].eliminated = true; // The candidate is deleted
            }
        }
    }
}
// Some parts were taken from the internet
// Mohammadreza_mokhtari_kia
