#include <cs50.h>
#include <stdio.h>

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
int victory_strength(pair pair);
void sort_pairs(void);
bool cycle(int source, int end);
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
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (name == candidates[i])
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count - 1; i++)
    {
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
    pair_count = 0;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
    return;
}

//Returns the victory strength of a winner-loser pair
int victory_strength(pair input_pair)
{
    return preferences[input_pair.winner][input_pair.loser] - preferences[input_pair.loser][input_pair.winner];
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair temp;   // Temporary placeholder

    //Bubble sort
    for (int sorted = 0; sorted < pair_count; sorted++)
    {
        for (int i = 0; i < pair_count - sorted - 1; i++)
        {
            if (victory_strength(pairs[i]) < victory_strength(pairs[i + 1]))
            {
                temp = pairs[i];
                pairs[i] = pairs[i + 1];
                pairs[i + 1] = temp;
            }
        }
    }
    return;
}

//Checks if a graph has a cycle
bool cycle(int source, int end)
{
    // Recursion base case
    if (source == end)
    {
        return true;
    }
    else
    {
        // Recursive step
        for (int i = 0; i < candidate_count; i++)
        {
            if (locked[end][i])
            {
                if (cycle(source, i))
                {
                    return true;
                }
            }
        }
    }
    return false;

}
// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // Locks pair if a cycle is not created
    for (int i = 0; i < pair_count; i++)
    {
        if (!cycle(pairs[i].winner, pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
{
    //Winner of graph has no losses
    int false_count;
    for (int i = 0; i < candidate_count; i++)
    {
        false_count = 0;
        for (int j = 0; j < candidate_count; j++)
        {
            if (!locked[j][i])
            {
                false_count++;
                if (false_count == candidate_count)
                {
                    printf("%s\n", candidates[i]);
                }
            }
        }
    }
    return;
}
