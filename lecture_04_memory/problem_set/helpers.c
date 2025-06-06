#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float red = image[i][j].rgbtRed;
            float green = image[i][j].rgbtGreen;
            float blue = image[i][j].rgbtBlue;

            int gray_pixel = round((red + green + blue) / 3);

            image[i][j].rgbtRed = gray_pixel;
            image[i][j].rgbtGreen = gray_pixel;
            image[i][j].rgbtBlue = gray_pixel;
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp_image[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp_image[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp_image[i][width - 1 - j];
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp_image[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp_image[i][j] = image[i][j];

            float red = 0;
            float green = 0;
            float blue = 0;
            int n = 0;

            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    int current_x = i + x;
                    int current_y = j + y;

                    if (current_x < 0 || current_x > (height - 1) ||
                        current_y < 0 || current_y > (width - 1))
                    {
                        continue;
                    }

                    red += image[current_x][current_y].rgbtRed;
                    green += image[current_x][current_y].rgbtGreen;
                    blue += image[current_x][current_y].rgbtBlue;
                    n++;
                }
            }

            tmp_image[i][j].rgbtRed = round(red / n);
            tmp_image[i][j].rgbtGreen = round(green / n);
            tmp_image[i][j].rgbtBlue = round(blue / n);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp_image[i][j];
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp_image[height][width];

    int gX[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1},
    };

    int gY[3][3] = {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1},
    };

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp_image[i][j] = image[i][j];

            int red_x = 0;
            int green_x = 0;
            int blue_x = 0;
            int red_y = 0;
            int green_y = 0;
            int blue_y = 0;

            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    int current_x = i + x;
                    int current_y = j + y;

                    if (current_x < 0 || current_x > (height - 1) ||
                        current_y < 0 || current_y > (width - 1))
                    {
                        continue;
                    }

                    red_x +=
                        gX[x + 1][y + 1] * image[current_x][current_y].rgbtRed;
                    green_x += gX[x + 1][y + 1] *
                               image[current_x][current_y].rgbtGreen;
                    blue_x +=
                        gX[x + 1][y + 1] * image[current_x][current_y].rgbtBlue;

                    red_y +=
                        gY[x + 1][y + 1] * image[current_x][current_y].rgbtRed;
                    green_y += gY[x + 1][y + 1] *
                               image[current_x][current_y].rgbtGreen;
                    blue_y +=
                        gY[x + 1][y + 1] * image[current_x][current_y].rgbtBlue;
                }
            }

            int red = round(sqrt((red_x * red_x) + (red_y * red_y)));
            int green = round(sqrt((green_x * green_x) + (green_y * green_y)));
            int blue = round(sqrt((blue_x * blue_x) + (blue_y * blue_y)));

            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }

            tmp_image[i][j].rgbtRed = red;
            tmp_image[i][j].rgbtGreen = green;
            tmp_image[i][j].rgbtBlue = blue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = tmp_image[i][j];
        }
    }
}
