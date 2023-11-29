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
    int blurOffset = 20;
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avR = 0;
            int avG = 0;
            int avB = 0;
            
            if (i - blurOffset >= 0 && j - blurOffset >= 0 && i + blurOffset <= height && j + blurOffset <= width)
            {
                for (int y = i - blurOffset; y < i + blurOffset; y++)
                {
                    for (int x = j - blurOffset; x < j + blurOffset; x++)
                    {
                        avR += image[y][x].rgbtRed;
                        avG += image[y][x].rgbtGreen;
                        avB += image[y][x].rgbtBlue;
                    }
                }

                int pixels = (blurOffset + blurOffset) * (blurOffset + blurOffset);

                avR /= pixels;
                avG /= pixels;
                avB /= pixels;
            }
            else
            {
                //first calculate how big to make the left right top and down box to blur
                int up = blurOffset;
                int down = blurOffset;
                int left = blurOffset;
                int right = blurOffset;

                while (i + up >= height)
                    up--;
                while (i - down <= 0)
                    down--;
                while (j - left <= 0)
                    left--;
                while (j + right >= width)
                    right--;

                for (int y = i - down; y < i + up; y++)
                {
                    for (int x = j - left; x < j + right   ; x++)
                    {
                        avR += image[y][x].rgbtRed;
                        avG += image[y][x].rgbtGreen;
                        avB += image[y][x].rgbtBlue;
                    }
                }

                int pixels = (left + right) * (up + down);

                avR /= pixels;
                avG /= pixels;
                avB /= pixels;
            }

            blurImage[i][j].rgbtRed = avR;
            blurImage[i][j].rgbtGreen = avG;
            blurImage[i][j].rgbtBlue = avB;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = blurImage[i][j];
        }
    }
    
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
