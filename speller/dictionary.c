// Implements a dictionary's functionality
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <cs50.h>
#include <string.h>
#include <strings.h>
#define LENGTH 45

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 187751;
unsigned int count = 0;

// Hash table
node *table[N];


// Returns true if word is in dictionary, else false
bool check(const char *word) //has to be case INsensitive
{
    //Obtain hash value
    int index = hash(word);
    if (table[index] == NULL)
    {
        return false;
    }

    //Access and traverse the linked list at index
    //Initialize a cursor pointer
    node *cursor = table[index];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            //Return true if found
            return true;
        }
        else
        {
        //Traverse down the linked list
        cursor = cursor->next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{

    //Hash function
    //Initialize hash to an arbitrary large number of buckets
    unsigned long hash = 400;
    int c = 0;
    while (*word != '\0')
    {
        c = tolower(*word);
        //Adding the ASCII value of the word after moving it 4 bits over
        hash = ((hash << 4) + c) % N;
        word++;
    }

    return hash;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    //Open dictionary file
    FILE *dict = fopen(dictionary, "r");
    if (dict == NULL)
    {
        printf("Dictionary not found");
        return false;
    }

    //Read strings from file in loop
    char word[LENGTH + 1];
    while(fscanf(dict, "%s", word) != EOF)
    {
        //Create new node for the word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Not enough memory, malloc unsuccessful");
            unload();
            return false;
        }

        //Copy word into the node
        strcpy(n->word, word);

        //Count number of words inputted
        count++;

        //Hash theh word
        int index = hash(word);

        //Insert the node at index
        // if (table[index] == NULL)
        // {
        //     // n->next = NULL;
        //     table[index] = n;

        // else
        {
            n->next = table[index];
            table[index] = n;
        }
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    //Create loop to iterate through array
    for (int i = 0; i < N; i++)
    {
        //Initialize temp and cursor
        node *temp = table[i];
        node *cursor = table[i];

        while (cursor != NULL)
        {
            //Move cursor to point at next one
            cursor = cursor->next;

            //Free the temp one
            free(temp);

            //Have temp point to what cursor is pointing to
            temp = cursor;
        }
    }
    return true;
}
