#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(void)
{
    printf("%lu, %lu\n", sizeof(BITMAPFILEHEADER), sizeof(BITMAPINFOHEADER));
}