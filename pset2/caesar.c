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
#define LOWER_CASE 97
#define UPPER_CASE 65  
#define ALPHABET_LETTERS 26
#define SPACE 32
check50 2013.pset3.find helpers.c

// declaration of functions
char conversion(int type, char char_in, int key);

int main(int argc, char* argv[])
{
    // checks to see if there are two arguments
    if (argc != 2)
    {
        printf("Please give 2 arguments\n");
        return 1;
    }
    
    // gets the key and turns it into an integer
    int key = atoi(argv[1]);
    
    // prompts user for string
    string string = GetString();
    
    // uses for-loop to convert into cyphertext
    for (int i = 0, n = strlen(string); i < n; i++)
    {
        // conditions for lower case letters
        if (islower(string[i]))
        {
            if (string[i] != SPACE)
            {
                string[i] = conversion(0, string[i], key);
            }
        }
            // conditions for uppercase letters
        else if (isupper(string[i]))
        {
            if (string[i] != SPACE)
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
    return 0;   
}

/**
* Converts ascii character of string to alphabet character, 
* shifts letter by key, and converts back to ASCII character 
*/
char conversion(int type, char char_in, int key)
{ 

    // declaration of variables
    int ascii_char = 0;
    int alpha_char = 0; 
    int cypher_alpha = 0;
    int cypher_ascii = 0; 
    int reducer = 0;
    char char_out = 0;
    
    // for lower case
    if (type == 0)
    {
        reducer = LOWER_CASE;
    }
    
    // for upper case
    if (type == 1)
    {
        reducer = UPPER_CASE;
    }
    
    ascii_char = char_in; 
    
    // subtracts ASCII character to alphabet
    alpha_char = ascii_char - reducer;  
    
    // adds key and shifts letters and wraps around
    cypher_alpha = (alpha_char + key) % ALPHABET_LETTERS;
    
    // adds number back to make ASCII value
    cypher_ascii = cypher_alpha + reducer; 
    
    // inputs ASCII value into char_out 
    char_out = cypher_ascii;
    
    // returns variable char_out from function to main
    return char_out;
}



