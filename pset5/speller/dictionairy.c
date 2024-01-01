// Implements a dictionary's functionality

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    node *temp = NULL; // temporary node for data of word to be saved to 
    int value = toupper(word[0] - 'A');

    temp->word = word; // set temp word to input word

    // if table[value] already pointing to a word, make that point to temp then set table[value] to point to temp
    if (table[value] -> next != NULL)
    {

    }

    // TODO: Improve this hash function
    return value;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        fclose(dict);
        return false;
    }

    // word is a temp value that stores the input from dictionary
    char word[LENGTH + 1]; 

    // writes 1 input from each line of dicitonary then gets the hash of it
    while (fscanf(dict, "%s", word) == 1)
    {
        int index = hash(word);
    }

    fclose(dict);
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    return false;
}
