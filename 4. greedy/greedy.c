/****************************************************************************
 * greedy.c
 *
 * Minor Programming
 * Najib el Moussaoui
 *
 * Convert amount of change owed into coins.
 ***************************************************************************/
#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float dollars;

    do
    {
        // prompt user for change owed in dollars
        printf("How much change is owed? ");
        dollars = get_float();
    }
    while (dollars < 0);

    // convert dollars to cents and round off
    float cents = round(dollars * 100);

    int amount = cents;

    // counter to keep track of amount of coints
    int count = 0;

    // substract quarters from amount, increment coin counter
    if (amount >= 25)
    {
        do
        {
            amount -= 25;
            count++;
        }
        while (amount >= 25);
    }
    // substract dimes from amount, increment coin counter
    if (amount >= 10)
    {
        do
        {
            amount -= 10;
            count++;
        }
        while (amount >= 10);
    }
    // substract nickels from amount, increment coin counter
    if (amount >= 5)
    {
        do
        {
            amount -= 5;
            count++;
        }
        while (amount >= 5);
    }
    // substract pennies from amount, increment coin counter
    if (amount >= 1)
    {
        do
        {
            amount -= 1;
            count++;
        }
        while (amount >= 1);
    }
    // print amount of coins to the console
    printf("Amount of coins: %i\n", count);
}