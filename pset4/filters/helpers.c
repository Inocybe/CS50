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
    int blurOffset = 1;
    
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

            /*
            //for each pixel in this image I shall form a box around it
            //making sure to check if it will go out of parameters though
            if (i - blurOffset <= 0 || j - blurOffset <= 0 || i + blurOffset >= height || j + blurOffset >= width)
            {
                //check for edges 
            }
            else
            {
                //add all values together around the thing and average them
                //first forms a box around the pixel, and values yeah
                for (int x = i - blurOffset, xbox = i + blurOffset; x < xbox; x++)
                {
                    for (int y = j - blurOffset, ybox = j + blurOffset; y < ybox; y++)
                    {
                        rAverage += image[x][y].rgbtRed;
                        gAverage += image[x][y].rgbtGreen;
                        bAverage += image[x][y].rgbtBlue;
                    }
                }
            }
            */
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
