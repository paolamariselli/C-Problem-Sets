/**
 * helpers.c
 *
 * Paola Mariselli
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdlib.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // if n is not positive, return false
    if (n <= 0)
    {
        return false;
    }
    
    //implement binary search algorithm
    int midpoint, first, last;
    
    first = 0;
    last = n - 1;
    midpoint = (first + last) / 2;
    
    while(first <= last)
    {
        if(values[midpoint] < value)
            first = midpoint + 1;
        else if(values[midpoint] == value)
            return true;
        else
            last = midpoint - 1;
        midpoint = (first + last) / 2;
    }
    return false;
    
    /**old linear search algorithm
    // implement linear searching algorithm
    for(int i = 0; i < n; i++)
    {
        if(values[i] == value)
        {
            return true;
            break;
        }
    }
    return false;
    */
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // implement an O(n^2) insertion sorting algorithm
    for(int i = 1; i < n; i++)
    {
        int element = values[i];
        int j = i;
        while(j > 0 && values[j - 1] > element)
        {
            values[j] = values[j - 1];
            j = j - 1;
        }
        values[j] = element;
    }
    return;
}
