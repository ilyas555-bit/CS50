/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // declaration of variables
    int min = 0; 
    int max = n - 1;
    
    // while-loop to conduct binary search
    while (min <= max)
    {
        int mid = (min + max) >> 1; 
        
        if (values[mid] == value)
        {
            // returns true if needle equals midpoint   
            return true;
        }
        else if (values[mid] < value)
        {
            // makes new minimum
            min = mid + 1;
        }
        else
        {
            // makes new maximum
            max = mid - 1;
        }
    }
    return false;
}
   
/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // declaration of variables
    int element = 0;
    int j = 0;
    
    // for-loop to sort values
    for(int i = 1; i < (n-1); i++)
    {
        element = values[i];
        j = i;
        while ((j > 0) && (values[j - 1] > element))
        {
            values[j] = values[j - 1];
            j--;
        }
        values[j] = element;
    }       
    return;
}


