// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

int word_count = 0;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Hash word to obtain a hash value
    int hash_value = hash(word);

    // Get linked list by index, in the hash table
    node *cursor = table[hash_value];

    // Traverse linked list, looking for the word
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Clear table
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Open dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Error while open dictionary\n");
        return false;
    }

    // Read strings from dictionary
    char buffer[LENGTH];

    while (fscanf(file, "%s", buffer) != EOF)
    {
        // Create a new node for each word
        node *new_word = malloc(sizeof(node));

        // Hash word to obtain a hash value
        int hash_value = hash(buffer);

        // Insert node into hash table at that location
        strcpy(new_word->word, buffer);

        new_word->next = table[hash_value];
        table[hash_value] = new_word;

        word_count++;
    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return word_count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Loop through the table
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        node *tmp = table[i];

        // Loop the cursor until the value is null
        while (cursor != NULL)
        {
            // Move the cursor
            // Free the memory
            // Point the tmp to the next word with the cursor
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }

    return true;
}
