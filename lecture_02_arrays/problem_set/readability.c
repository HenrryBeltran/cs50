#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int get_letters_count(string text);
int get_words_count(string text);
int get_sentences_count(string text);

int main(void)
{
    const string text = get_string("Text: ");
    const int letters_count = get_letters_count(text);
    const int words_count = get_words_count(text);
    const int sentences_count = get_sentences_count(text);

    const float L = (float)letters_count / words_count * 100.0;
    const float S = (float)sentences_count / words_count * 100.0;

    int index = round(0.0588 * L - 0.296 * S - 15.8);

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 0 && index < 16)
    {
        printf("Grade %i\n", index);
    }
    else
    {
        printf("Grade 16+\n");
    }
}

int get_letters_count(string str)
{
    int count = 0;
    for (int i = 0, n = strlen(str); i < n; i++)
    {
        if (isalpha(str[i]))
        {
            count++;
        }
    }
    return count;
}

int get_words_count(string str)
{
    int letters_count = 0;
    int words_count = 0;

    for (int i = 0, n = strlen(str); i < n; i++)
    {
        if (!isspace(str[i]))
        {
            letters_count++;
        }
        else if (isspace(str[i]) && letters_count > 0)
        {
            words_count++;
            letters_count = 0;
        }
    }

    if (letters_count > 0)
    {
        words_count++;
    }

    return words_count;
}

int get_sentences_count(string str)
{
    int letters_count = 0;
    int sentences_count = 0;

    for (int i = 0, n = strlen(str); i < n; i++)
    {
        if (!ispunct(str[i]) && !isspace(str[i]))
        {
            letters_count++;
        }
        else if ((str[i] == '.' || str[i] == '!' || str[i] == '?') &&
                 letters_count > 0)
        {
            sentences_count++;
            letters_count = 0;
        }
    }

    if (letters_count > 0)
    {
        sentences_count++;
    }

    return sentences_count;
}
