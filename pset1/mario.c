/**
 * mario.c
 *
 * Thuy (Lucy) Nam
 * lucynam@college.harvard.edu
 *
 * This program prompts the user for an input and uses the value to 
 * recreate a half-pyramid for mario using hashes (#) for blocks.
 */

#include <stdio.h>
#include <cs50.h>

int main(void)

{

    // declare variable height
    int height; 

    // Do-while loop checks for valid input from user
    do 
    {
        printf("Please pick a number between 0 and 23:\n");
        height = GetInt(); 
    }
    while (height < 0 || height > 23); 

    /* for loops draws the half pyramid by printing spaces, 
       printing hashbars, and printing enter */
    for (int row = 0; row < height; row++)
    {
        for (int space = 0; space < abs(row - (height - 1)); space++)
        {
            printf(" ");
        }
        for (int hash = 0; hash < row + 2; hash++)
        {
            printf("#"); 
        }
        printf("\n");
    }
    return(0);
}



