#include <stdio.h>

typedef int integer;

int main(void)
{
    char *s = "HI!";

    for (int i = 0; i < 3; i++)
    {
        printf("%c", *(s + i));
    }
    printf("\n");
}
