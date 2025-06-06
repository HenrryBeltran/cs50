#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;

    do
    {
        height = get_int("Height: ");
    } while (height < 1);

    for (int i = 0; i < height; i++)
    {
        int space_index = height - i - 2;
        for (int j = 0; j < height; j++)
        {
            if (space_index < j)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
}
