#include <math.h>
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
            int average = (red + green + blue + 1) / 3;
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
    RGBTRIPLE holdImage[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0, w = width; j < w; j++)
        {
            holdImage[i][j] = image[i][width - j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = holdImage[i][j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blurImage[height][width];
    int blurOffset = 1;
    
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
    RGBTRIPLE temp[height][width];

    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gxBlue = 0;
            int gyBlue = 0;
            int gxGreen = 0;
            int gyGreen = 0;
            int gxRed = 0;
            int gyRed = 0;

            for (int r = -1; r < 2; r++)
            {
                for (int c = -1; c < 2; c++)
                {
                    if (i + r < 0 || i + r > height - 1)
                    {
                        continue;
                    }
                    if (j + c < 0 || j + c > width - 1)
                    {
                        continue;
                    }

                    gxBlue += image[i + r][j + c].rgbtBlue * gx[r + 1][c + 1];
                    gyBlue += image[i + r][j + c].rgbtBlue * gy[r + 1][c + 1];
                    gxGreen += image[i + r][j + c].rgbtGreen * gx[r + 1][c + 1];
                    gyGreen += image[i + r][j + c].rgbtGreen * gy[r + 1][c + 1];
                    gxRed += image[i + r][j + c].rgbtRed * gx[r + 1][c + 1];
                    gyRed += image[i + r][j + c].rgbtRed * gy[r + 1][c + 1];
                }
            }

            int blue = round(sqrt(gxBlue * gxBlue + gyBlue * gyBlue));
            int green = round(sqrt(gxGreen * gxGreen + gyGreen * gyGreen));
            int red = round(sqrt(gxRed * gxRed + gyRed * gyRed));

            temp[i][j].rgbtBlue = (blue > 255) ? 255 : blue;
            temp[i][j].rgbtGreen = (green > 255) ? 255 : green;
            temp[i][j].rgbtRed = (red > 255) ? 255 : red;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
        }
    }

    return;
}
