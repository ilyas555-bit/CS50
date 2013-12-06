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
    
    #define LOWER_CASE 97;
    #define UPPER_CASE 65;  
    #define ALPHABET_LETTERS 26;
    
    // declaration of variables
    int ascii_array[strlen(string)];
    int alpha_array[strlen(string)];
    int cypher_alpha[strlen(string)];
    int cypher_ascii[strlen(string)];
    
    for (int i = 0, n = strlen(string); i < n; i++)
    {
        // conditions for lower case letters
        if (islower(string[i]))
        {
            if (string[i] != 32)
            {
                // turns string into array of ASCII values
                ascii_array[i] = string[i]; 
                // turns array of ASCII values into array of alphabet letters
                alpha_array[i] = ascii_array[i] - LOWER_CASE;  
                // shifts letters by integers of key
                cypher_alpha[i] = (alpha_array[i] + key) % ALPHABET_LETTERS;
                // turns alphabet letters back to ASCII
                cypher_ascii[i] = cypher_alpha[i] + LOWER_CASE;
                // turns ASCII back to string
                string[i] = cypher_ascii[i];
            }
        }
            // conditions for uppercase letters
        else if (isupper(string[i]))
        {
            if (string[i] != 32)
            {
                // turns string into array of ASCII values
                ascii_array[i] = string[i]; 
                // turns array of ASCII values into array of alphabet letters
                alpha_array[i] = ascii_array[i] - UPPER_CASE;  
                // shifts letters by integers of key
                cypher_alpha[i] = (alpha_array[i] + key) % ALPHABET_LETTERS;
                // turns alphabet letters back to ASCII
                cypher_ascii[i] = cypher_alpha[i] + UPPER_CASE;
                // turns ASCII back to string
                string[i] = cypher_ascii[i];
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

