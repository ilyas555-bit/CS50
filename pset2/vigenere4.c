/**
 * vigenere.c
 *
 * Thuy (Lucy) Nam
 * lucynam@college.harvard.edu
 *
 * This program takes a command line argument and prompts the user 
 * for a string and uses the Vigenere Cypher to encode it.
 */

#include <stdio.h>
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
    
    // makes sure that the letters in the argument is in the alphabet
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (isalpha(argv[1][i]) == 0)
        {
            return 1;
        }
    }
    
    // turns argument letters into ASCII
    int ascii_key[strlen(argv[1])];
    int key[strlen(argv[1])];
    
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        // conditions for lower case argument
        if (islower(argv[1][i]))
        {
            // turns argument into ASCII
            ascii_key[i] = argv[1][i];
            // turns ascii into alphabet
            key[i] = ascii_key[i] - 97;
        }
        
        // conditions for upper case argument
        if (isupper(argv[1][i]))
        {
            // turns argument into ASCII
            ascii_key[i] = argv[1][i];
            // turns ASCII into alphabet
            key[i] = ascii_key[i] - 65; 
        }
    }
    
    // prompt user for string
    string string = GetString();

    // declaration of variables
    int ascii_array[strlen(string)];
    int alph[strlen(string)];
    int cyph[strlen(string)];
    int cypher_ascii[strlen(string)];
    int space = 0; 
    
    for (int i = 0, n = strlen(string); i < n; i++)
    {
        // adds one to space counter each time string encounters a space
        if (string[i] == 32)
        {
            space++;
        }     
            
        // conditions for lower case letters
        if (islower(string[i]))
        {
            if (string[i] != 32)
            {
                // turn string into array of ascii values
                ascii_array[i] = string[i]; 
                // turn array of ascii values into array of alphabet letters
                alph[i] = ascii_array[i] - 97;  
                // add alpha letters from string to alpha letters from argument
                cyph[i] = ((alph[i] + key[(i - space) % strlen(argv[1])]) % 26);
                // turn cypher_alpha back to ASCII
                cypher_ascii[i] = cyph[i] + 97;
                // turn ASCII to letters
                string[i] = cypher_ascii[i];
            }
        }
        else if (isupper(string[i]))
        {
            // conditions for uppercase letters
            if (string[i] != 32)
            {
                // turn string into array of ASCII values
                ascii_array[i] = string[i]; 
                // turn array of ASCII values into array of alphabet letters
                alph[i] = ascii_array[i] - 65;  
                // add alpha letters from string to alpha letters from argument
                cyph[i] = ((alph[i] + key[(i - space) % strlen(argv[1])]) % 26);
                // turn cypher_alpha back to ASCII
                cypher_ascii[i] = cyph[i] + 65;
                // turn ASCII to letters
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
 
