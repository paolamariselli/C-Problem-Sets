/**
 * greedy.c
 *
 * Paola Mariselli
 *
 * Uses a greedy algorithm to determine how many coins are necessary to make change for a user-provided dollar amount.
 */

#include <stdio.h>
#include <cs50.h>
#include <math.h>

#define CENTS_PER_DOLLAR 100
#define QUARTER 25
#define DIME 10
#define NICKEL 5
#define PENNY 1

int main(void)
{
    float changeowedf;
    
    //get positive money for how much change is owed
    do
    {
    printf("How much change is owed?\n");
    changeowedf = GetFloat();
    }
    while (changeowedf < 0);
    
    //convert float to int, multiply by 100, round
    int changeowed = round(changeowedf * CENTS_PER_DOLLAR);
    
    //initiate coinsused
    int coinsused = 0;
    
    //loop for quarters
    while (QUARTER <= changeowed)
    {
        changeowed -= QUARTER;
        coinsused++;
    }
    
    //loop for dimes
    while (DIME <= changeowed)
    {
        changeowed -= DIME;
        coinsused++;
    }
    
    //loop for nickels
    while (NICKEL <= changeowed)
    {
        changeowed -= NICKEL;
        coinsused++;
    }
    
    //loop for pennies
    while (PENNY <= changeowed)
    {
        changeowed -= PENNY;
        coinsused++;
    }
    
    //display total number of coins used
    printf("%i\n", coinsused);

    return 0;
}
