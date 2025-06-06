#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

bool only_26_letters(int argc, string argv[]);
string transform(string key, string text);

int main(int argc, string argv[])
{
    if (!only_26_letters(argc, argv))
    {
        return 1;
    }

    const string key = argv[1];
    const string plaintext = get_string("plaintext: ");
    const string ciphertext = transform(key, plaintext);

    printf("ciphertext: %s\n", ciphertext);
}

bool only_26_letters(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s key\n", argv[0]);
        return false;
    }

    int len = strlen(argv[1]);

    if (len != 26)
    {
        printf("Key must contain 26 characters.\n");
        return false;
    }

    for (int i = 0; i < len; i++)
    {
        char x_letter = toupper(argv[1][i]);
        for (int j = 0; j < len; j++)
        {
            if (x_letter == toupper(argv[1][j]) && i != j)
            {
                printf("Key can not repeat the same character.\n");
                return false;
            }
        }
    }

    for (int i = 0; i < len; i++)
    {
        if (!isalpha(argv[1][i]))
        {
            printf("Usage: %s key\n", argv[0]);
            return false;
        }
    }

    return true;
}

string transform(string key, string text)
{
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]) && islower(text[i]))
        {
            int idx = text[i] - 'a';
            text[i] = tolower(key[idx]);
        }
        else if (isalpha(text[i]) && isupper(text[i]))
        {
            int idx = text[i] - 'A';
            text[i] = toupper(key[idx]);
        }
    }

    return text;
}
