#include "cs50.h"
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }
        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        //checks each candidate to see if input == name
        if (strcmp(candidates[i], name) == 0)
        {
            //if input == name, update ranks array to rank, then i will be candidate
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    //first pointer
    for (int i = 0; i < candidate_count; i++)
    {
        //second pointer
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    //pointer to sort through first part 2d array
    for (int i = 0; i < candidate_count; i++)
    {
        //pointer to sort through second part 2d array
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > 0 && preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    for (int j = 0; j < pair_count; j++)
    {
        bool swap = false;
        for (int i = 0; i < pair_count; i++) 
        { 
            //compares winner strength of one to other to see which one is possible better (bubble sort)
            if (preferences[pairs[i-1].winner][pairs[i-1].loser] > preferences[pairs[i].winner][pairs[i].loser]) 
            {
                //if first value greater then second value, it swaps value
                int winnerTrack = pairs[i].winner;
                int loserTrack = pairs[i].loser;
                
                //actual swapping
                pairs[i].winner = pairs[i-1].winner;
                pairs[i].loser = pairs[i-1].loser;
                pairs[i-1].winner = winnerTrack;
                pairs[i-1].loser = loserTrack;

                //adding to swap count, if swap count stayed 0, everything is all sorted
                swap = true;
            }
        }
        if (!swap)
        {
            return;
        }
    }  
    return;
}

//Cycle will go through candidates and see if it creates a cycle, if it does returns false
bool Cycle(int winner, int loser)
{
    if (locked[loser][winner])
    {
        return true;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        //checks who loser wins over, and if i goes back to the winner, or if anyone i wins over goes back to winner
        if (locked[loser][i] && Cycle(winner, i))
        {
            return true;
        }
    }
    return false;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    //array to store amount total votes each candidate has 
    for (int i = 0; i < pair_count; i++)
    {
        //if isnt a cycle, it will be true
        if (!Cycle(pairs[i].winner, pairs[i].loser))
            locked[pairs[i].winner][pairs[i].loser] = true;
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool lossed = false;
        
        //makes sure a candidate doesn't lose once if it does, indication will be false
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                lossed = true;
                break;
            }
        }

        if (lossed)
            continue;
        else
        {
            printf("%s\n", candidates[i]);
            return;
        }

    }
    return;
}