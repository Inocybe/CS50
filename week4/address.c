#include "cs50.h"
#include <stdio.h>

int main(void)
{
    char *s = "HI!";
    int i = get_int("Where would you like to poke around: ");
    printf("%s\n", *(s+i));
} 