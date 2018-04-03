/****************************************************************************
 * caesar.c
 *
 * Programmeren I
 * Problem set 2 (Crypto)
 * Minor Programmeren
 * Najib el Moussaoui
 *
 * Input a key, and cipher your input-text by +key. (single integer)
 ***************************************************************************/

#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

void convert();
int c;
string t;

int main(int argc, string argv[])
{
    // check if argc is 2, else stop program

    if (argc != 2)
    {
        return 1;
    }

    // pulling key type string from argv[] & convert to type int

    string key = argv[1];
    int k = atoi(key);

    // prompt for plain text to cipher

    printf("plaintext: ");

    t = get_string();

    // output ciphertext

    printf("ciphertext: ");

    // loop over prompt text to cipher

    for (int i = 0, n = strlen(t); i < n; i++)
    {
        convert(t[i], k);
    }
    printf("\n");
}

// function that converts

void convert(letter, key)
{
    if (isupper(letter))
    {
        c = ((letter - 'A') + key) % 26;
        printf("%c", c + 'A');
    }
    else if (islower(letter))
    {
        c = ((letter - 'a') + key) % 26;
        printf("%c", c + 'a');
    }
    else
    {
        printf("%c", letter);
    }
}

