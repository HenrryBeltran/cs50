#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

const int LETTERS_LENGTH = 26;
const int POINTS[] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                      1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int get_points(string word);

int main(void)
{
    string player1_word = get_string("Player 1: ");
    string player2_word = get_string("Player 2: ");

    int player1_points = get_points(player1_word);
    int player2_points = get_points(player2_word);

    if (player1_points > player2_points)
    {
        printf("Player 1 wins!\n");
    }
    else if (player1_points < player2_points)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int get_points(string word)
{
    int points = 0;
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        int character = toupper(word[i]);
        for (int j = 0; j < LETTERS_LENGTH; j++)
        {
            if (character == j + 'A')
            {
                points += POINTS[j];
                break;
            }
        }
    }
    return points;
}
