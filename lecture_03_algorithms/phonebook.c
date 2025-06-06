#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    string names;
    string numbers;
} person;

int main(void)
{
    person persons[] = {
        {"Carter", "+1-617-495-1000"},
        {"David", "+1-617-495-1000"},
        {"John", "+1-949-468-2750"},
    };

    string name = get_string("Name: ");
    for (int i = 0; i < 3; i++)
    {
        if (strcmp(persons[i].names, name) == 0)
        {
            printf("Found %s\n", persons[i].numbers);
            return 0;
        }
    }
    printf("Not found\n");
    return 1;
}
