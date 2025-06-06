#include <cs50.h>
#include <stdio.h>

bool clamp(int value, int min, int max);

int main(void)
{
    int height;

    do
    {
        height = get_int("Height: ");
    } while (clamp(height, 1, 8) == false);

    int width = (height * 2) + 2;
    for (int i = 0; i < height; i++)
    {
        int left_space = height - i - 2;
        for (int j = 0; j < width; j++)
        {
            int right_space = width - left_space - 1;
            if (left_space < j && j < height)
            {
                printf("#");
            }
            else if (right_space > j && j > height + 1)
            {
                printf("#");
            }
            else if (right_space <= j)
            {
                printf("\n");
                break;
            }
            else
            {
                printf(" ");
            }
        }
    }

    // Last break line
    printf("\n");
}

bool clamp(int value, int min, int max)
{
    if (value < min)
    {
        return false;
    }
    else if (value > max)
    {
        return false;
    }
    else
    {
        return true;
    }
}
