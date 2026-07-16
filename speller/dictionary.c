// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include "dictionary.h"

unsigned int word_count = 0;

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
#define N 676

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    int index = hash(word);
    node *current = table[index];
    while (current != NULL)
    {
        if (strcasecmp(current->word, word) == 0)
        {
            return true;
        }
    current = current->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int first = toupper(word[0]) - 'A';
    int second = 0;
    if (word[1] != '\0' && isalpha(word[1]))
    {
        second = toupper(word[1]) - 'A';
    }
    return first * 26 + second;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }
    char word[LENGTH + 1];
    while (fscanf(file, "%s", word) != EOF)
    {
        word_count++;
        node *n = malloc(sizeof(node));
        strcpy(n->word, word);
        int index = hash(word);
        n->next = table[index];
        table[index] = n;
    }
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (word_count > 0)
    {
        return word_count;
    }
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
void free_list(node *n)
{
    if (n == NULL)
    {
        return;
    }
    free_list(n->next);
    free(n);
}

bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        free_list(table[i]);
    }
    return true;
}

