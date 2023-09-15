#include "cs50.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX 9

typedef struct
{
    string name;
    int votes;
}
candidate;

candidate candidates[MAX];

int main()
{
    printf("%i\n", sizeof(candidates));
}