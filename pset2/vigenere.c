/**
 * vigenere.c
 *
 * Paola Mariselli
 *
 * Encrypts user-supplied plaintext using a Vigenere cipher.
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
    string keyword = argv[1];
    int keyword_length = strlen(keyword);
//make sure argument is alphabetical
    for (int i=0, n=strlen(keyword); i<n; i++)
    {
        if (!isalpha(keyword[i]))
        {
            printf("Please provide alphabetical argument\n");
            return 1;
        }
    }
//obtain plaintext and set to p
    string plaintext;
    do
    {
    plaintext = GetString();
    }
    while (plaintext == NULL);
//encrypt plaintext and track letters
    int num_letters_seen = 0;
    for (int i=0, n=strlen(plaintext); i<n; i++)
    {
        //only encrypt if is alphabetical
        if (isalpha(plaintext[i]))
        {
            //turn keyword letter into an integer key
            int newkeyword;
            if (isupper(keyword[num_letters_seen % keyword_length]))
            {
                newkeyword = keyword[num_letters_seen % keyword_length] - 65;
            }
            else
            {
                newkeyword = keyword[num_letters_seen % keyword_length] - 97;
            }
            if (isupper(plaintext[i]))
            {
                plaintext[i] = ((plaintext[i] - 65 + newkeyword) % 26) + 65;
            }
            else if (islower(plaintext[i]))
            {
                plaintext[i] = ((plaintext[i] - 97 + newkeyword) % 26) + 97;
            }
            num_letters_seen++;
        }
    }
    printf("%s\n", plaintext);
    
    return 0;
}
