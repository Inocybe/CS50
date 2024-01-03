// Implements a dictionary's functionality

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>
#include <stdbool.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 676;

// Hash table
node *table[N];

// Word Count
int word_count = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);
    
    node *p = table[index]; // pointer

    while (p != NULL)
    {
        if (strcasecmp(word, p->word) == 0)
            return true;
        p = p->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned long index = 0;
    for (int i = 0, l = strlen(word); i < l; i++)
    {
        index += tolower(word[i]);
    }
    return index % N;
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

    node *temp = NULL; // temporary node for data of word to be saved to 
    char word[LENGTH + 1];

    // writes 1 input from each line of dicitonary then gets the hash of it
    while (fscanf(dict, "%s", word) != EOF)
    {
        int index = hash(word);
        
        temp = malloc(sizeof(node));
        if (temp == NULL)
        {
            fclose(dict);
            return false;
        }
        strcpy(temp->word, word); // set temp word to input word

        temp->next = table[index];
        table[index] = temp;
    }

    fclose(dict);
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
    for (int i = 0; i < N; i++)
    {
        node *p = table[i];
        while (p)
        {
            node *tmp = p;
            p = tmp->next;
            free(tmp);
        }
        if (p == NULL)
        {
            return true;
        }
        
    }
    return false;
}
