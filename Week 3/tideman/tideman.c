#include <cs50.h>
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
} pair;

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
bool is_on_ballot(string name);
int get_index(string name);
int get_SOV(pair p);
bool pointed_at(int candidate);
bool pointing(int candidate);
bool check_cycle(int start, int end);

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
    if (is_on_ballot(name))
    {
        ranks[rank] = get_index(name);
        return true;
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
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i; j < candidate_count; j++)
        {
            if (preferences[i][j] != preferences[j][i])
            {
                if (preferences[i][j] > preferences[j][i])
                {
                    pairs[pair_count].winner = i;
                    pairs[pair_count].loser = j;
                }
                else
                {
                    pairs[pair_count].winner = j;
                    pairs[pair_count].loser = i;
                }
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    pair temp;
    bool done;
    do
    {
        done = true;
        for (int i = 0; i < pair_count - 1; i++)
        {
            if (get_SOV(pairs[i]) < get_SOV(pairs[i + 1]))
            {
                temp = pairs[i];
                pairs[i] = pairs[i + 1];
                pairs[i + 1] = temp;
                done = false;
            }
        }
    } while (!done);

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int p = 0; p < pair_count; p++)
    {
        if (!check_cycle(pairs[p].loser, pairs[p].winner))
        {
            locked[pairs[p].winner][pairs[p].loser] = true;
        }
    }

    return;
}

// Print the winner of the election
void print_winner(void)
{
    int source;

    for (int i = 0; i < candidate_count; i++)
    {
        if (!pointed_at(i) && pointing(i))
        {
            source = i;
        }
    }

    printf("%s\n", candidates[source]);
    return;
}

bool is_on_ballot(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            return true;
        }
    }
    return false;
}

int get_index(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            return i;
        }
    }
    return -1;
}

int get_SOV(pair p)
{
    return preferences[p.winner][p.loser] - preferences[p.loser][p.winner];
}

bool pointed_at(int candidate)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][candidate])
        {
            return true;
        }
    }
    return false;
}

bool pointing(int candidate)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[candidate][i])
        {
            return true;
        }
    }
    return false;
}

bool check_cycle(int start, int end)
{
    if (locked[start][end] || start == end)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[start][i])
        {
            if (check_cycle(i, end))
            {
                return true;
            }
        }
    }

    return false;
}