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
bool is_a_cycle(int origin, int target);
void print_winner(void);
void merge(pair arr[], int left, int middle, int rigth);
void sort(pair arr[], int left, int rigth);

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
        if (strcmp(candidates[i], name) == 0)
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
    int strength;
    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            strength = preferences[i][j] - preferences[j][i];
            if (strength > 0)
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (strength < 0)
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    sort(pairs, 0, pair_count - 1);
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        int winner = pairs[i].winner;
        int loser = pairs[i].loser;

        if (is_a_cycle(winner, loser) == false)
        {
            locked[winner][loser] = true;
        }
    }
}

bool is_a_cycle(int origin, int target)
{
    if (origin == target)
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        bool found_locked = locked[target][i];
        if (found_locked == true)
        {
            if (is_a_cycle(origin, i) == true)
            {
                return true;
            }
        }
    }

    return false;
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool is_winner = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i] == true)
            {
                is_winner = false;
                break;
            }
        }

        if (is_winner == true)
        {
            printf("%s\n", candidates[i]);
        }
    }
}

void merge(pair arr[], int left, int middle, int rigth)
{
    int i, j, k;
    int left_len = middle - left + 1;
    int rigth_len = rigth - middle;

    // Create temp arrays
    pair temp_left[left_len], temp_rigth[rigth_len];

    // Copy data to temp arrays
    for (i = 0; i < left_len; i++)
    {
        temp_left[i] = arr[left + i];
    }
    for (j = 0; j < rigth_len; j++)
    {
        temp_rigth[j] = arr[middle + 1 + j];
    }

    // Merge the temp arrays back into arr[]
    i = 0;
    j = 0;
    k = left;
    while (i < left_len && j < rigth_len)
    {
        int left_winner = temp_left[i].winner;
        int left_loser = temp_left[i].loser;
        int left_strength = preferences[left_winner][left_loser] -
                            preferences[left_loser][left_winner];

        int rigth_winner = temp_left[i].winner;
        int rigth_loser = temp_left[i].loser;
        int rigth_strength = preferences[rigth_winner][rigth_loser] -
                             preferences[rigth_loser][rigth_winner];

        if (left_strength > rigth_strength)
        {
            arr[k] = temp_left[i];
            i++;
        }
        else
        {
            arr[k] = temp_rigth[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of temp_left[],
    // if there are any
    while (i < left_len)
    {
        arr[k] = temp_left[i];
        i++;
        k++;
    }

    // Copy the remaining elements of temp_rigth[],
    // if there are any
    while (j < rigth_len)
    {
        arr[k] = temp_rigth[j];
        j++;
        k++;
    }
}

void sort(pair arr[], int left, int rigth)
{
    if (left < rigth)
    {
        int middle = left + (rigth - left) / 2;

        // Sort first and second halves
        sort(arr, left, middle);
        sort(arr, middle + 1, rigth);

        merge(arr, left, middle, rigth);
    }
}
