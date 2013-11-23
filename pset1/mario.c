/**
 * mario.c
 *
 * Paola Mariselli
 *
 * Prints out a half pyramid with a user-supplied height.
 */

#include <stdio.h>
#include <cs50.h>

#define MAX_HEIGHT 23

int main(void)
{
    // request and validate height
    int height;
    do
    {
        printf ("Height: ");
        height = GetInt();
    }
    while (height < 0 || height > MAX_HEIGHT);
    
    // print the pyramid from the top down
    for (int line = 0; line < height; line++)
    {
        // print spaces
        for (int space = 0; space <= height - (line + 2); space++)
        {
            printf (" ");
        }
        
        // print hashes
        for (int hash = 0; hash <= line + 1; hash++)
        {
            printf ("#");
        }
        
    // go to next line
    printf ("\n");
    }

    return 0;
}

