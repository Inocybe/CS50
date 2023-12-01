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
    int blurOffset = 100;
    
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
    RGBTRIPLE edgeImage[height][width];

    int y_arrayGx[3] = {1, 2, 1};
    int x_arrayGx[3] = {1, 0, -1};

    int y_arrayGy[3] = {1, 0, -1};
    int x_arrayGy[3] = {1, 2, 1};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int rG;
            int gG;
            int bG;
            
            int rGx = 0;
            int gGx = 0;
            int bGx = 0;

            int rGy = 0;
            int gGy = 0;
            int bGy = 0;

            //counter to y arrays 
            int y_arrayCounter = 0;

            //go threw a box around the chosen pixel and will add to the color values 
            for (int y = i - 1; y < i + 2; y++)
            {
                //counter to x arrays
                int x_arrayCounter = 0;

                for (int x = j - 1; x < j + 2; x++)
                {
                    int r = 0;
                    int g = 0;
                    int b = 0;

                    if (y >= 0 && x >= 0 && y + 3 <= height && x + 3 <= width)
                    {
                        r = image[y][x].rgbtRed;
                        g = image[y][x].rgbtGreen;
                        b = image[y][x].rgbtBlue;
                    }

                    //access values from Gx and Gy arrays I created I need a counter to tell which valeus to access

                    //add values of pixel to Gx ints
                    //got equation from https://wikimedia.org/api/rest_v1/media/math/render/svg/283009fe2306c03eff7308aebba2242d8c82cc71 
                    rGx += ((r * x_arrayGx[x_arrayCounter]) * y_arrayGx[y_arrayCounter]);
                    gGx += ((g * x_arrayGx[x_arrayCounter]) * y_arrayGx[y_arrayCounter]);
                    bGx += ((b * x_arrayGx[x_arrayCounter]) * y_arrayGx[y_arrayCounter]);

                    rGx += ((r * x_arrayGy[x_arrayCounter]) * y_arrayGy[y_arrayCounter]); 
                    gGy += ((g * x_arrayGy[x_arrayCounter]) * y_arrayGy[y_arrayCounter]);
                    bGy += ((b * x_arrayGy[x_arrayCounter]) * y_arrayGy[y_arrayCounter]);

                    x_arrayCounter++;
                }

                y_arrayCounter++;
            }

            //got equation from https://wikimedia.org/api/rest_v1/media/math/render/svg/23ae6772c5f58751fc6014b71d6adafb30a31c79                    
            rG = sqrt((rGx * rGx) + (rGy * rGy));
            gG = sqrt((gGx * gGx) + (gGy * gGy));
            bG = sqrt((bGx * bGx) + (bGy * bGy));

            if (rG > 255)
                rG = 255;
            if (gG > 255)
                gG = 255;
            if (bG > 255)
                bG = 255;

            edgeImage[i][j].rgbtRed = rG;
            edgeImage[i][j].rgbtGreen = gG;
            edgeImage[i][j].rgbtBlue = bG;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = edgeImage[i][j];
        }
    }

    return;
}
