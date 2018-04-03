/****************************************************************************
 * vigenere.c
 *
 * Programmeren I
 * Problem set 2 (Crypto)
 * Minor Programmeren
 * Najib el Moussaoui
 *
 * Input a key, and cipher your input-text by +key (alphabetical word)
 ***************************************************************************/

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

// initialize function
bool convert();

int main(int argc, string argv[])
{

    // check if argument count passed in to main is 2
    if (argc != 2)
    {
        printf("Error1\n");
        return 1;
    }

    // pull phrase to use for cipher from argv[1], store in variable key
    string key = argv[1];

    // loop over argv[1] to check if input is all alphabetical
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (!isalpha(key[i]))
        {
            printf("Error2\n");
            return 1;
        }
    }

    // prompt for plain text to cipher
    printf("plaintext: ");
    string t = get_string();

    // output ciphertext
    printf("ciphertext: ");
    for (int i = 0, n = strlen(t), j = 0; i < n; i++)
    {
        bool converted = convert(t[i], key[j]);
        if (converted)
        {
            j = (j + 1) % strlen(key);
        }
    }

    printf("\n");
}

// function that takes plain text and key to convert to ciphertext
bool convert(letter, key)
{
    int keyalpha;
    int c;

    // check if letter in key is lower of upper, substract by ASCII value
    if (isupper(key))
    {
        keyalpha = key - 'A';
    }
    else if (islower(key))
    {
        keyalpha = key - 'a';
    }

    // convert to ciphertext
    if (isupper(letter))
    {
        c = ((letter - 'A') + keyalpha) % 26;
        printf("%c", c + 'A');
        return true;
    }
    else if (islower(letter))
    {
        c = ((letter - 'a') + keyalpha) % 26;
        printf("%c", c + 'a');
        return true;
    }
    else
    {
        printf("%c", letter);
        return false;
    }
}

