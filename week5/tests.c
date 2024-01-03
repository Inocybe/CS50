#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    char *word = malloc(sizeof(char) * 2);
    word[0] = 'A';
    word[1] = 'b';

    int x = toupper(word[0]) - 'A';

    printf("%i\n", x);

    free(word);
}