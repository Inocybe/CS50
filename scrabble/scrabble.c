#include "cs50.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

string lower(string s);
int calculator(string s);
void who_win(int x, int y);

int main(void)
{
    string p1 = get_string("Player 1: ");
    string p2 = get_string("Player 2: ");
    
    int p1_score = calculator(lower(p1));
    int p2_score = calculator(lower(p2));

    who_win(p1_score, p2_score);
}

string lower(string s)
{
    for (int i = 0, l = strlen(s); i < l; i++)
    {
        if (islower(s[i]))
        {
            s[i] = tolower(s[i]);
        }
    }

    return s;
}

int calculator(string s)
{
    int points [26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};
    int score = 0;

    for (int i = 0, l = strlen(s); i < l; i++)
    {
        char target = s[i]; 
        if (target > 96 && target < 123)
        {
            int x = target - 97;
            score += points[x];
        }
    }
}

void who_win(int x, int y)
{
    if (x > y)
    {
        printf("Player 1 wins!");
    }
    else if (x < y)
    {
        printf("Player 2 wins!");
    }
    else
    {
        printf("Tie!");
    }
}
