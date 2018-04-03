/****************************************************************************
 * mario.c (more)
 *
 * Minor Programming
 * Najib el Moussaoui
 *
 *     #  #
 *    ##  ##
 *   ###  ###
 *  ####  ####
 * #####  #####
 *
 * Prompt a height of a pyramid and print that pyramid to the console.
 ***************************************************************************/
#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // variable for height of the pyramid
    int height;
    // prompt user for height
    do
    {
        printf("Height of the pyramid (in blocks): ");
        height = get_int();
    }
    while (height < 0 || height > 23);
    // counters that keep track of hashes and spaces
    int hashes = height - 1;
    int spaces = height - 1;
    // for loop that prints amount of rows equal to height
    for (int row = 0; row < height; row++)
    {
        // for loop that prints spaces (left)
        for (int spaceL = 0; spaceL < spaces; spaceL++)
        {
            printf(" ");
        }
        // for loop that prints hashes (left)
        for (int hashL = 0; hashL < (height - hashes); hashL++)
        {
            printf("#");
        }
        // standard print two spaces between pyramid halves
        printf("  ");

        // for loop that prints hashes (right)
        for (int hashR = 0; hashR < (height - hashes); hashR++)
        {
            printf("#");
        }
        // decrement spaces and hashes counters
        spaces--;
        hashes--;
        // line break per line of pyramid
        printf("\n");
    }
}

