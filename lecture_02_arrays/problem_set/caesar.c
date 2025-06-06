#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int ALPHABETH = 26;

bool only_digits(int argc, string argv[]);
string rotate(int key, string text);

int main(int argc, string argv[])
{
    if (!only_digits(argc, argv))
    {
        return 1;
    }

    const int key = abs(atoi(argv[1]) % ALPHABETH);
    const string plaintext = get_string("plaintext: ");
    const string ciphertext = rotate(key, plaintext);

    printf("ciphertext: %s\n", ciphertext);
}

bool only_digits(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s key\n", argv[0]);
        return false;
    }

    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (isalpha(argv[1][i]))
        {
            printf("Usage: %s key\n", argv[0]);
            return false;
        }
    }

    return true;
}

string rotate(int key, string text)
{
    string rotate_text = text;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            rotate_text[i] = text[i] + key;
            if (!isalpha(rotate_text[i]))
            {
                rotate_text[i] -= ALPHABETH;
            }
        }
    }

    return rotate_text;
}
