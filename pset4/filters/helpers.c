#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //find the highest value rbg then make all the other colors match
            int red = image[i][j].rgbtRed;
            int green = image[i][j].rgbtGreen;
            int blue = image[i][j].rgbtBlue;
            int average = (red + green + blue) / 3;
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0, w = width / 2; j < w; j++)
        {
            //RGBTRIPLE hold = malloc(sizeof(RGBTRIPLE));
            RGBTRIPLE hold = image[i][j];
            image[i][j] = image[i][width - j];
            image[i][width - j] = hold;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE blurImage[height][width];
    int blurOffset = 1;

    for (int i = blurOffset; i < width - blurOffset; i++)
    {
        for (int j = blurOffset; j < height -  blurOffset; j++)
        {
            int averageR = 0;
            int averageG = 0;
            int averageB = 0;
            /*
            average.rgbtRed = 0x00;
            average.rgbtGreen = 0x00;
            average.rgbtBlue = 0x00;
            */

            for (int x = i - 1, xbox = i + 1; x < xbox; x++)
            {
                for (int y = j - 1, ybox = j + 1; y < ybox; y++)
                {
                    averageR += image[y][x].rgbtRed;
                    averageG += image[y][x].rgbtGreen;
                    averageB += image[y][x].rgbtBlue;
                }
            }

            blurImage[j][i].rgbtRed = averageR / 8;
            blurImage[j][i].rgbtGreen = averageG / 8;
            blurImage[j][i].rgbtBlue = averageB / 8;
        }
    }

    for (int i = blurOffset; i < width - blurOffset; i++)
    {
        for (int j = blurOffset; j < height -  blurOffset; j++)
        {
            image[j][i] = blurImage[j][i];
        }
    }
    
    /*  *****STARTING OVER******
    for (int i = blurOffset, hb = height - blurOffset; i < hb; i += (blurOffset + 2))
    {
        for (int j = blurOffset, wb = width - blurOffset; j < wb; j += (blurOffset + 2))
        {
            RGBTRIPLE average;
            average.rgbtRed = 0;
            average.rgbtGreen = 0;
            average.rgbtBlue = 0;

            for (int x = i - blurOffset, xbox = i + blurOffset; x < xbox; x++)
            {
                for (int y = j - blurOffset, ybox = j + blurOffset; y < ybox; y++)
                {
                    average.rgbtRed += image[x][y].rgbtRed;
                    average.rgbtGreen += image[x][y].rgbtGreen;
                    average.rgbtBlue += image[x][y].rgbtBlue;
                }
            }

            average.rgbtRed = average.rgbtRed / ((blurOffset + 2) * (blurOffset + 2));
            average.rgbtGreen = average.rgbtGreen / ((blurOffset + 2) * (blurOffset + 2));
            average.rgbtBlue = average.rgbtBlue / ((blurOffset + 2) * (blurOffset + 2));
            
            for (int x = i - blurOffset, xbox = i + blurOffset; x < xbox; x++)
            {
                for (int y = j - blurOffset, ybox = j + blurOffset; y < ybox; y++)
                {
                    image[x][y].rgbtRed = average.rgbtRed;
                    image[x][y].rgbtGreen = average.rgbtGreen;
                    image[x][y].rgbtBlue = average.rgbtBlue;
                }
            }
        }
    }
    */
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
