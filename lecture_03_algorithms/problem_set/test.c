#include <cs50.h>
#include <stdio.h>

typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

int main(void)
{
    int voter_count = 4;
    int candidate_count = 3;
    candidate candidates[candidate_count];
    candidates[0].name = "Foo";
    candidates[0].votes = 2;
    candidates[0].eliminated = false;

    candidates[1].name = "Bar";
    candidates[1].votes = 1;
    candidates[1].eliminated = false;

    candidates[2].name = "Baz";
    candidates[2].votes = 1;
    candidates[2].eliminated = false;

    int min = voter_count;

    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == true)
        {
            continue;
        }

        if (candidates[i].votes < min)
        {
            min = candidates[i].votes;
        }
    }
    printf(">> %i\n", min);
}
