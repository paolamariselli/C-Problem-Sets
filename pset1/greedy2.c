/**
 * greedy2.c
 *
 * Paola Mariselli
 *
 * Uses a greedy algorithm to determine how many coins are necessary to make change for a user-provided dollar amount. Does some div/mod math to make the problem super simple.
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
    
    //figure out how many coins for quarters
    coinsused += changeowed / QUARTER;
    
    //figure out remainder left
    changeowed = changeowed % QUARTER;
    
    //same for dimes
    coinsused += changeowed / DIME;
    changeowed = changeowed % DIME;
    
    //same for nickels
    coinsused += changeowed / NICKEL;
    changeowed = changeowed % NICKEL;
    
    //similar for pennies
    coinsused += changeowed;
    
    //display total number of coins used
    printf("%i\n", coinsused);

    return 0;
}
