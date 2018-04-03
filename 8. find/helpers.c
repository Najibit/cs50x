/**
 * helpers.c
 *
 * Programming I
 * Minor Programming
 * Najib el Moussaoui
 *
 * Helper functions for Problem Set 3.
 */

#include <cs50.h>
#include <stdio.h>
#include "helpers.h"
#include <string.h>

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    // index dimensions (left, right and middle)
    int l = 0;
    int r = n;
    int m = (r + l) / 2;

    // ensure size is valid
    if (n <= 0)
    {
        return false;
    }

    // binary search to find value in array
    while (n > 0)
    {
        if (values[m] == value)
        {
            return true;
        }
        else if (values[m] > value)
        {
            r = m - 1;
            m = (r + l) / 2;
            n = n / 2;
        }
        else if (values[m] < value)
        {
            l = m + 1;
            m = (r + l) / 2;
            n = n / 2;
        }
    }
    return false;
}

/**
 * Sorts array of n values.
 */

void sort(int values[], int n)
{
    // make count array with index 0 up to MAX
    int MAX = 65536;
    int count[MAX];

    // remove garbage values from array
    memset(count, 0, sizeof(count));

    // index for value array
    int k = 0;

    // count sort values from values array to count array
    for (int i = 0; i < n; i++)
    {
        count[values[i]]++;
    }

    // refill values array from count array
    for (int j = 0; j < MAX - 1; j++)
    {
        while (count[j] > 0)
        {
            values[k] = j;
            k++;
            count[j]--;
        }
    }
}
