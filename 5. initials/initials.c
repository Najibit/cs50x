/****************************************************************************
 * initials.c
 *
 * Programmeren I
 * Problem set 2 (Crypto)
 * Minor Programmeren
 * Najib el Moussaoui
 *
 * Print initials of a name.
 ***************************************************************************/


#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    // prompt user for name

    string name = get_string();

    // check if there are spaces in front

    if (name[0] != ' ')
    {
        printf("%c", toupper(name[0]));
    }

    // if no spaces, execute this code block

    for (int i = 0, n = strlen(name) - 1; i < n; i++)
    {
        if (name[i] == ' ' && name[i + 1] != ' ')
        {
            printf("%c", toupper(name[i + 1]));
        }
    }
    printf("\n");
}

