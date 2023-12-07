#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("Usage: ./recouver IMAGE.raw\n");
        return 1;
    }

    FILE *input = fopen(argv[1], r);
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    //for checkFor[3] make sure to do bitwise arithmatic check buffer[3] == checkFor[3]
    checkFor[4] = {0xff, 0xd8, 0xff, 0xe0};

    int size = sizeof(*input);

    for (int i = 0; i < size; i++)
    {
        //iterate through untill find 
    }



}