#include <stdio.h>
#include "cs50.h"

int main(void)
{
    int h;
    do
    {
        h = get_int("Height: ");
    } 
    while (h < 1 || h > 9);

    /*each line of mario, also tell how many boxs and spaces to add.
    i.e. if line 0, add 7 spaces 1 box | line 2, add 6 spaces 2 box*/
    for (int i = 0; i < h; i++)
    {
        int pointer = h - i - 1;
        int count = 0;
        while (count < h)
        {
            if (count < pointer)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
            count++;
        }
        printf(" ");
        for (int j = 0; j < i + 1; j++)
        {
            printf("#");
        }


        printf("\n");
    }
    
}