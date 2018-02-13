// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include "dictionary.h"

typedef struct node
{
    bool is_word;
    // For every letter in alphabet and '\''
    struct node *children[27];
}
node;

void unload_node(node *trav);
unsigned int size_count(node *trav);

node *root;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *trav = root;
    int index;

    for (int i = 0; word[i] != '\0'; i++, trav = trav->children[index])
    {
        // Case-insensitive
        if (isalpha(word[i]))
        {
            // ASCII of 'a' is 97(0x61)
            index = tolower(word[i]) % 0x61;
        }
        else
        {
            // For '\'' set its index to the last
            index = 26;
        }

        // i-th character is NULL
        if (!trav->children[index])
        {
            return false;
        }
    }

    // Find the word
    return trav->is_word;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary
    FILE *dict = fopen(dictionary, "r");
    if (!dict)
    {
        fclose(dict);
        fprintf(stderr, "Could not open %s.\n", dictionary);
        return false;
    }

    char word[LENGTH + 1];
    root = calloc(1, sizeof(node));
    if (!root)
    {
        unload();
        return false;
    }

    // For every word in dictionary, iterate through the trie
    while (fscanf(dict, "%s", word) != EOF)
    {
        int index = 0;
        node *trav = root;

        // Each element in children corresponds to a different letter
        for (int i = 0; word[i] != '\0'; i++)
        {
            // Calculate the index
            if (isalpha(word[i]))
            {
                // ASCII of 'a' is 97(0x61)
                index = tolower(word[i]) % 0x61;
            }
            else
            {
                // For '\'' set its index to the last
                index = 26;
            }

            // Check the value at children[i]
            // If NULL
            if (trav->children[index] == NULL)
            {
                trav->children[index] = calloc(1, sizeof(node));
                if (!trav->children[index])
                {
                    unload();
                    return false;
                }
                trav = trav->children[index];
            }
            // If not NULL, move to new node and continue
            else
            {
                trav = trav->children[index];
            }
        }
        // At end of a word, set is_word to true
        trav->is_word = true;
    }

    // Close file
    fclose(dict);

    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    node *trav = root;

    unsigned int count = size_count(trav);

    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Successful unload
    unload_node(root);

    return true;
}

unsigned int size_count(node *trav)
{
    unsigned int counter = 0;

    // Check for is_word
    if (trav->is_word == true)
    {
        counter = 1;
    }

    // Then iterate through all the children of a node
    for (int i = 0; i < 27; i++)
    {
        // For a non-NULL child
        if (trav->children[i])
        {
            counter += size_count(trav->children[i]);
        }
    }

    // All the children is NULL
    return counter;
}

void unload_node(node *trav)
{
    // Check every child in trav->children
    for (int i = 0; i < 27; i++)
    {
        // For non-NULL child, free the child
        if (trav->children[i] != NULL)
        {
            unload_node(trav->children[i]);
        }
    }

    // Then free the node
    free(trav);
}
