#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (image[i][j].rgbtRed == 0x00 && image[i][j].rgbtBlue == 0x00 && image[i][j].rgbtGreen == 0x00)
            {
                image[i][j].rgbtBlue = 0xff;
            }
        }
    }
}
