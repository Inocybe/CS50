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
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);
    
    node *p = table[index]; // pointer

    while (p->next != NULL)
    {
        if (strcasecmp(word, p->word) == 0)
            return true;
        else
            p = p->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0] - 'A');
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    // word is a temp value that stores the input from dictionary
    char word[LENGTH + 1]; 

    node *temp = NULL; // temporary node for data of word to be saved to 

    // writes 1 input from each line of dicitonary then gets the hash of it
    while (fgets(word, LENGTH + 1, dict))
    {
        int index = hash(word);
        printf("%i\n", index);

        temp = (node*)malloc(sizeof(node));
        strcpy(temp->word, word); // set temp word to input word

        // if table[index] already pointing to a word, make that point to temp then set table[index] to point to temp
        if (table[index]->next != NULL)
        {
            temp->next = table[index]->next;
            table[index]->next = temp;
        }
        else
        {
            table[index]->next = temp;
        }
    }

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    int counter = 0;

    for (int i = 0; i < N; i++)
    {
        node *p = table[i];
        while (p->next != NULL)
        {
            counter++;
            p = p->next;
        }
    }

    return counter;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    node *p = NULL;
    
    for (int i = 0; i < N; i++)
    {
        //still items in list to free
        while (table[i]->next != NULL)
        {
            p = table[i]->next;
            // still links to free
            while(p->next != NULL)
                p = p->next;

            if (p->next == NULL)
                free(p);
        }
    }

    return true;
}
