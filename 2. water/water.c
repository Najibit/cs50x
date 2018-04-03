/****************************************************************************
 * water.c
 *
 * Minor Programming
 * Najib el Moussaoui
 *
 * Convert the amount of minutes that you shower into bottles of water.
 ***************************************************************************/
#include <cs50.h>
#include <stdio.h>



int main(void)
{
    // prompt user for amount of minutes showered
    printf("How many minutes do you shower? ");
    int minutes = get_int();
    // convert to bottles water and print to console
    printf("You shower: %i minutes\n", minutes);
    printf("Amount in bottles of water: %i\n", minutes * 12);
}
