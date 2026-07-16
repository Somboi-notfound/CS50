#include "helpers.h"
#include <math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE (*copy)[width] = malloc(height * sizeof(RGBTRIPLE[width]));
    int Gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int Gy[3][3] =
    {
        {-1, -2, -1},
        { 0,  0,  0},
        { 1,  2,  1}
    };
    for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width ; j++)
            {
                 copy[i][j] = image[i][j];
            }
        }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width ; j++)
        {
            int GxG = 0;
            int GyG = 0;
            int GxR = 0;
            int GyR = 0;
            int GxB = 0;
            int GyB = 0;
            for (int di = -1; di <= 1; di++)
            {
                for (int dj = -1; dj <= 1; dj++)
                {
                    int ni = i + di;
                    int nj = j + dj;
                    int ci = 1 + di;
                    int cj = 1 + dj;
                    if (nj >= 0 && ni >=0 && ni < height && nj < width)
                    {
                        GxG += copy[ni][nj].rgbtGreen * Gx[ci][cj];
                        GyG += copy[ni][nj].rgbtGreen * Gy[ci][cj];
                        GxR += copy[ni][nj].rgbtRed * Gx[ci][cj];
                        GyR += copy[ni][nj].rgbtRed * Gy[ci][cj];
                        GxB += copy[ni][nj].rgbtBlue * Gx[ci][cj];
                        GyB += copy[ni][nj].rgbtBlue * Gy[ci][cj];
                    }
                }
            }
            int red = round(sqrt(GxR * GxR + GyR * GyR));
            int blue = round(sqrt(GxB * GxB + GyB * GyB));
            int green = round(sqrt(GxG * GxG + GyG * GyG));
            if (red > 255)
            {
                red = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }
            if (green > 255)
            {
                green = 255;
            }

            image[i][j].rgbtRed = red;
            image[i][j].rgbtBlue = blue;
            image[i][j].rgbtGreen = green;

        }
    }
    free(copy);
    return;
}