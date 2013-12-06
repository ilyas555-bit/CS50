/**
 * caesar.c
 *
 * Thuy (Lucy) Nam
 * lucynam@college.harvard.edu
 *
 * This program takes a command line argument and prompts the user 
 * for a string and uses the Caesar Cypher to encode it.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>
#include <ctype.h>
#define LOWER_CASE 97;
#define UPPER_CASE 65;  
#define ALPHABET_LETTERS 26;

char conversion(int type, char char_in, int key);

int main(int argc, char* argv[])
{
    // checks to see if there are two arguments
    if (argc != 2)
    {
        return 1;
    }
    // get the key and turn it into an integer
    
    int key = atoi(argv[1]);
    
    // prompt user for string
    string string = GetString();
    
    for (int i = 0, n = strlen(string); i < n; i++)
    {
        // conditions for lower case letters
        if (islower(string[i]))
        {
            if (string[i] != 32)
            {
                string[i] = conversion(0, string[i], key);
            }
        }
            // conditions for uppercase letters
        else if (isupper(string[i]))
        {
            if (string[i] != 32)
            {
               string[i] = conversion(1, string[i], key);
            }     
        }
    }  
        
    // prints out the cyphertext
    for (int cyphertext = 0; cyphertext < strlen(string); cyphertext++)
    {
        printf("%c", string[cyphertext]);
        }  
    printf("\n");
    
    
    
}

char conversion(int type, char char_in, int key)
{ 
    int ascii_char_in=0;
    int alpha_char_in = 0; 
    int cypher_alpha = 0;
    int cypher_ascii = 0; 
    int reducer = 0;
    char char_out = 0;
    
    if(type == 0)
    {
     reducer = LOWER_CASE;
    }
    if(type == 1)
    {
        reducer = UPPER_CASE;
    }
    ascii_char_in = char_in; 
    alpha_char_in = ascii_char_in - reducer;  
    cypher_alpha = (alpha_char_in + key) % ALPHABET_LETTERS;
    cypher_ascii = cypher_alpha + reducer;  
    char_out = cypher_ascii;
    return char_out;
}



