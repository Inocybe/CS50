#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    char word[2] = {'1', 'I'};

    int x = toupper(word[0] - 'A');

    printf("%i\n", x);
}