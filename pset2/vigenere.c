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
#define LOWER_CASE 97
#define UPPER_CASE 65
#define ALPHABET_LETTERS 26
#define SPACE 32
#define COMMA 44

// declaration of functions
char conv(int type, char char_in, int key);
int convert_key(int type, char char_in);

int main(int argc, char* argv[])
{
    
    // checks to see if there are two arguments
    if (argc != 2)
    {
        printf("Please give 2 arguments\n");
        return 1;
    }
   
    // checks that letters in the argument is in the alphabet
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        if (isalpha(argv[1][i]) == 0)
        {
            printf("Enter alphabetical letters for 2nd argument\n");
            return 1;
        }
    }
    
    // declaration of variables
    int key[strlen(argv[1])];
    int space = 0;
    
    // uses for-loop to convert key to ASCII value 
    for (int i = 0, n = strlen(argv[1]); i < n; i++)
    {
        // conditions for lower case argument
        if (islower(argv[1][i]))
        {
            key[i] = convert_key(0, argv[1][i]);
        }
        
        // conditions for upper case argument
        if (isupper(argv[1][i]))
        {
            key[i] = convert_key(1, argv[1][i]);
        }
    }
    
    // prompt user for str
    string str = GetString();
    
    // for-loop that stays at same key letter when passing 'space' or 'comma'
    for (int i = 0, n = strlen(str); i < n; i++) 
    {   
        if (str[i] == SPACE || str[i] == COMMA)
        {
            space++;
        }            
        
        // conditions for lower case letters
        if (islower(str[i]))
        {
            if (str[i] != SPACE)
            {
                str[i] = conv(0, str[i], key[(i - space) % strlen(argv[1])]);
            }
        }
        else if (isupper(str[i]))
        {
            // conditions for uppercase letters
            if (str[i] != SPACE)
            {
                str[i] = conv(1, str[i], key[(i - space) % strlen(argv[1])]);
            }    
        } 
    }  
    
    // uses for-loop to print out cyphertext
    for (int cyphertext = 0; cyphertext < strlen(str); cyphertext++)
    {
        printf("%c", str[cyphertext]);
    }  
    printf("\n");  
    return 0;  
}
 
/**
* Converts ascii character of str to alphabet character, 
* shifts letter by key, and converts back to ASCII character 
*/
char conv(int type, char char_in, int key)
{ 
    
    // declaration and initialization of variables
    int ascii_char = 0;
    int alpha_char = 0; 
    int cypher_alpha = 0;
    int cypher_ascii = 0; 
    int reducer = 0;
    char char_out = 0;
    
    // for lower case
    if ( type == 0)
    {
        reducer = LOWER_CASE;
    }
    
    // for upper case
    if ( type == 1)
    {
        reducer = UPPER_CASE;
    }
    
    ascii_char = char_in; 
    
    // subtracts ASCII character to alphabet
    alpha_char = ascii_char - reducer; 
    
    // adds key and shifts letters and wraps around if necessary
    cypher_alpha = (alpha_char + key) % ALPHABET_LETTERS;

    // adds number back to make ASCII value 
    cypher_ascii = cypher_alpha + reducer;
    
    // inputs cypher_ascii into variable char_out  
    char_out = cypher_ascii;
    
    // returns char_out from function to main
    return char_out;
}

/**
Converts characters in key to ASCII values
*/
int convert_key(int type, char char_in)
{

    // declaration and initialization of variables
    int ascii_key = 0;
    int key = 0;
   
    ascii_key = char_in;
    
    // condition for lower case
    if (type == 0)
    {
        key = ascii_key - LOWER_CASE;
    }
    
    // condition for upper case
    if (type == 1)
    {
        key = ascii_key - UPPER_CASE;
    }       
    
    // returns variable key from function to main
    return key; 
 }              
