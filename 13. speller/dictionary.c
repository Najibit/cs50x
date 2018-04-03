/**
 * dictionary.c
 *
 * Programming II
 * Minor Programming
 * Najib el Moussaoui
 *
 *
 * Implements a dictionary's functionality.
 *
 * functions
 * load: loads a dictionary in a tries data structure.
 * check: checks input text on misspelled words.
 * size: reports size of input text in words.
 * unload: frees memory using the free_my_memories() function.
 */
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "dictionary.h"
#include <cs50.h>
#include <ctype.h>
#include <string.h>



typedef struct node
{
    bool is_word;
    struct node *children[27];
}
node;

// node prototypes
node *root;
node *parent;
node *cursor;
node *child;

// unload function prototype
bool free_my_memories(node *cursor);

// word counter
int wordies = 0;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    // create a cursor and set it to root
    node *cursor = root;

    // loop over input words and check if nodes exists
    for (int i = 0, n = strlen(word); i < n; i++)
    {
        if (isalpha(word[i]))
        {
            // convert to lower case
            char letter = tolower(word[i]);

            // if there is no node, word is misspelled, else move cursor
            if (cursor->children[letter - 'a'] == NULL)
            {
                return false;
            }
            else
            {
                cursor = cursor->children[letter - 'a'];
            }
        }
        // same, but for if letter is apostrophe
        if (word[i] == '\'')
        {
            if (cursor->children[26] == NULL)
            {
                return false;
            }
            else
            {
                cursor = cursor->children[26];
            }
        }
    }

    // return true for the word, so spelled correctly
    return cursor->is_word;
}

/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)

{
    // allocate memory for root node
    root = calloc(1, sizeof(node));

    // make a copy of root node to use
    node *parent = root;

    // filepointer for dictionary
    FILE *fp = fopen(dictionary, "r");

    // abort if dictionary not loaded
    if (fp == NULL)
    {
        fprintf(stderr, "Cannot not open %s.\n", dictionary);
        unload();
        return false;
    }

    // loop over dictionary text and store in tries
    for (char c = fgetc(fp); c != EOF; c = fgetc(fp))
    {
        //  in case of alphabetical character
        if (isalpha(c))
        {
            // if there is no child node
            if (parent->children[c - 'a'] == NULL)
            {
                // allocate memory and create child node, set equal to parent
                child = calloc(1, sizeof(node));
                parent->children[c - 'a'] = child;
                parent = child;
            }
            else
            {
                parent = parent->children[c - 'a'];
            }
        }
        // in case of apostrophe
        else if (c == '\'')
        {
            // if no node, create one
            if (parent->children[26] == NULL)
            {
                child = calloc(1, sizeof(node));
                parent->children[26] = child;
                parent = child;
            }
            // else move parent node to child's position
            else
            {
                parent = parent->children[26];
            }
        }
        // check for end of word
        else if (c == '\n' || c == '\0')
        {
            // update word counter
            wordies++;

            // mark as whole word
            parent->is_word = true;

            // reset parent node to root values
            parent = root;
        }
    }
    // close file
    fclose(fp);

    // return true to load()
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return wordies;
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    // unload with recursion
    return free_my_memories(root);
}

bool free_my_memories(node *cursor)
{
    // loop over every pointer in childrens' arrays
    for (int i = 0; i < 27; i++)
    {
        // recursively check for pointers
        if (cursor->children[i] != NULL)
        {
            free_my_memories(cursor->children[i]);
        }
    }

    // free the cursor is all pointers are NULL
    free(cursor);

    return true;
}