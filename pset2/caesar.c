/**
 * caesar.c
 *
 * Paola Mariselli
 *
 * Encrypts user-supplied plaintext using a Caesar cipher.
 */

#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{ 
//make sure only one argument is passed
    while (argc != 2)
    {
        printf("Please provide one argument\n");
        return 1;
    }  
//set k to argument obtained
    int k = atoi(argv[1]);
//make sure argument is positive
    while (k < 0)
    {
        printf("Please provide positive argument\n");
        return 1;
    }
//obtain plaintext and set to n
    string word = GetString();
//actualy cyphering
    for (int i=0, n=strlen(word); i<n; i++)
    {
        if (isalpha(word[i]))
        {
            if (isupper(word[i]))
            {
                int newupperletter = ((word[i] - 65 + k) % 26) + 65;
                printf ("%c", newupperletter);
            }
            else if (islower(word[i]))
            {
                int newlowerletter = ((word[i] - 97 + k) % 26) + 97;
                printf ("%c", newlowerletter);
            }
        }
        else
        {
            printf ("%c", word[i]);
        }
    }
    printf ("\n");

    return 0;
}
