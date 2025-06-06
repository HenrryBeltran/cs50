#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    const string strings[] = {"battleship", "boot",    "cannon",
                              "iron",       "thimble", "top hat"};

    const string str = get_string("String: ");
    for (int i = 0; i < 6; i++)
    {
        if (strcmp(strings[i], str) == 0)
        {
            printf("Found\n");
            return 0;
        }
    }
    printf("Not found\n");
    return 1;
}
