// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

unsigned int len_linked(node *list);
int dict_size;

// Number of buckets in hash table
const unsigned int N = 10000;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    //Determines position in hash table
    int position = hash(word);

    //Iterates through linked list
    node *n = table[position];
    while (n != NULL)
    {
        if (strcasecmp(word, n->word) == 0)
        {
            return true;
        }
        n = n->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word) //djb2 by Dan Bernstein
{
    unsigned long hash = 5381;
    int c = *word;

    while (*word != 0)
    {
        hash = ((hash << 5) + hash) + tolower(c);
        c = *word++;
    }
    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //Opens dictionary file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];
    int position; //Placeholder for position of word in hash table
    while (fscanf(dict, "%s", word) != EOF)
    {
        //Hash function
        position = hash(word);

        //Adds new node to hash table
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return 1;
        }
        strcpy(n->word, word); //Copies word into node
        n->next = table[position]; // Connects new node to head
        table[position] = n; //Makes new node the head
        dict_size++;

    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    //Iterates through hash table
    for (int i = 0; i < N; i++)
    {
        //Iterates through linked list at each bucket
        node *n = table[i];
        while (n != NULL)
        {
            node *tmp = n;
            n = n->next;
            free(tmp);
        }
        if (n == NULL && i == N - 1)
        {
            return true;
        }
    }
    return false;
}

//Calculates the length of a linked list recursively
unsigned int len_linked(node *list)
{
    //Base case
    if (list->next == NULL)
    {
        return 0;
    }
    else
    {
        //Recursive step
        return 1 + len_linked(list->next);
    }
}