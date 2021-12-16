// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Useing in Hash func
#define MULTIPLIER 37

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 5000;

// Hash table
node *table[N];

int dict_size = 0;


// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // create var copy[length of word]
    char copy[strlen(word)];

    // start loop in length of word
    for (int i = 0; i <  strlen(word - 1); i++)
    {
        // copy[i] = convert word[i] to lower
        copy[i] = tolower(word[i]);
    }

    // get index value from hash func
    int index = hash(copy);

    // crate node and add teble pointer in node
    node *n = table[index];


    while (n != NULL)
    {
        if (strcmp(n->word, copy) == 0)
        {
            return true;
        }
        n = n->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // create var to set long number
    unsigned long h;
    // create var pointer to word
    unsigned const char *us;

    us = (unsigned const char *) word;

    h = 0;
    while (*us != '\0')
    {
        // 0 * 37 * ascii number
        h = h * MULTIPLIER + *us;

        // stop conditon
        us++;
    }

    // return h value % N
    return h % N;

}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open file
    FILE *file_pointer = fopen(dictionary, "r");

    // check file is open or not.
    if (!file_pointer)
    {
        return false;
    }

    // init words array
    char next_word[LENGTH + 1];

    // read words from file
    while (fscanf(file_pointer, "%s", next_word) != EOF)
    {
        // create new node for words
        node *n = malloc(sizeof(node));

        if (n == NULL)
        {
            return false;
        }

        //copy char from node
        strcpy(n->word, next_word);

        // hash word to get index value
        int index = hash(next_word);

        // insert node in hash table as location
        n->next = table[index];
        table[index] = n;

        dict_size++;
    }

    // close file
    fclose(file_pointer);
    return true;

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // return dict size
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        // assign cursor
        node *n = table[i];

        while (n != NULL)
        {
            // add n in temp
            node *temp = n;
            // n = next pointer
            n = n->next;
            // delete temp from memorey
            free(temp);
        }

        if (n == NULL && i == N - 1)
        {
            return true;
        }
    }
    return false;
}
