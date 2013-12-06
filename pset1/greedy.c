/**
 * greedy.c
 *
 * Thuy (Lucy) Nam
 * lucynam@college.harvard.edu
 *
 * This program prompts the user for amount of change owed and calculates
 * the least number of coins that can be returned.
 */


#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)

{

    // variable declarations
    float change;  
    int quarters = 0;
    int dimes = 0;
    int nickels = 0; 
    int pennies = 0; 

    /* prompts user for amount of change and Do-while loop checks for 
    valid input from user (valid = non negative float)*/
    do 
    {
        printf("How much change is owed?\n");
        change = GetFloat(); 
    }
    while (change < 0); 
    
    // declare variable money
    int money = round(change * 100); 
    
    /* uses division and modulo math inside if-loops to decrease money 
    value by the largest coin possible. Variables (declared above) are
    used to keep count of how many coins are used */
    if (money >= 25)
    {
        quarters = money / 25;
        money = money % 25; 
    }
    if (money >= 10)
    {  
        dimes = money / 10; 
        money = money % 10; 
    }
    if (money >= 5)
    {
        nickels = money / 5;
        money = money % 5; 
    }
    if (money >= 1)
    {
        pennies = money / 1; 
        money = money % 1;
    }
    
    // variable coins adds up number of coins used  
        int coins = quarters + dimes + nickels + pennies; 
        
    // prints number of coins used
    printf("%d\n", coins); 
    return(0);
    }


