/****************************************************************************
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Implements a dictionary's functionality.
 ***************************************************************************/
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "dictionary.h"
#define SIZE 27

// declares a new type called node which happens to be a struct. 
typedef struct node
{
   bool is_word;
   struct node* children[SIZE];
} node;

// declares a node pointer called root.     
node* root;

// initialization of number of words to be 0. 
int numofwords = 0;  

/**
* Returns true if word is in dictionary else false.
*/
bool check(const char* word)
{
    int i = 0; 
   
    // initialized node pointer called cursor to equal root.
    node* cursor = root;
   
    // uses a while loop to iterate over the word. 
    while (word[i] != '\0')
    {   
        char num = word[i];
        
        // condition that accounts for the apostrophe.
        if (word[i] == '\'')
        {
            num = 'z' + 1;   
        }     
        int newnum = tolower(num) - 'a';
        
        // condition to check if children is not NULL and moves there.
        if (cursor->children[newnum] != NULL)
        {
            cursor = cursor->children[newnum];
            i++;
        }
        else 
        {
            return false; 
        }
    }
    // upon reaching the end, checks what you have found is a word. 
    if (cursor->is_word == true)
    {
        return true; 
    }
    return false;

  }     

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    // opens the dictionary file.
    FILE* dict = fopen(dictionary, "r"); 
    
    // checks if the dictionary file is NULL.
    if (dict == NULL)
    {
        printf("Could not open dictionary file");
        return false;
    }
    
    // mallocs memory in the heap for the root. 
    root = malloc(sizeof(node));
    
    // sets node pointer called cursor to root. 
    node* cursor = root; 
    
    // initializes letter to 0. 
    int let = 0; 
    
    // uses a while loop to iterate over the file. 
    while (fgetc(dict) != EOF)
    {     
        fseek(dict, -1, SEEK_CUR);
        cursor = root; 
        
        // for loop to iterate over each word.
        for  (let = fgetc(dict); let != '\n'; let = fgetc(dict))
        {
            // deals with apostrophes.
            if (let == '\'')
            {
                let = 'z' + 1;
                
            }
            
            // if the child associated with the letter is NULL, mallocs a node.
            if (cursor->children[let - 'a'] == NULL)
            {
                cursor->children[let - 'a'] = malloc(sizeof(node));
                cursor = cursor->children[let - 'a'];
            } 
            
            // if letter is there, follow the pointer. 
            else
            { 
                cursor = cursor->children[let - 'a']; 
            }
        }
        
        // at the end, sets the word to true. 
        cursor->is_word = true; 
        
        // increases number of words by 1. 
        numofwords++;
    }
     
    // closes dictionary file. 
    fclose(dict);
   
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    // returns number of words calculated in load. 
    return numofwords;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool freenode(node* current)
{
    // recursively free each of current's children. 
    for (int i = 0; i < SIZE; i++)
    {
        if (current->children[i] != NULL)
        {
            freenode(current->children[i]);
        }    
    }
    
    // then free current. 
    free(current);
    return true;
}

/**
 * Uses function freenode to unload dictionary from memory. 
 */
bool unload(void)
{
    return freenode(root);
}

