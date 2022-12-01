#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //Sets RGB values to their average
    BYTE avg;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            avg = round(((float) image[y][x].rgbtBlue + image[y][x].rgbtGreen + image[y][x].rgbtRed) / 3);
            image[y][x].rgbtBlue = avg;
            image[y][x].rgbtGreen = avg;
            image[y][x].rgbtRed = avg;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //Reverses each row of pixels
    RGBTRIPLE tmp;
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width / 2; x++)
        {
            tmp = image[y][x];
            image[y][x] = image[y][width - x - 1];
            image[y][width - x - 1] = tmp;
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Creates a reference image
    RGBTRIPLE imagecp[height][width];
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            imagecp[y][x] = image[y][x];
        }
    }

    //Number of averaged pixels
    int no_avg, r, g, b;

    //Averages pixels
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            no_avg = 0;
            r = 0;
            b = 0;
            g = 0;
            for (int dx = -1; dx <= 1; dx++)
            {
                for (int dy = -1; dy <= 1; dy++)
                {
                    //Checks if projected pixel is within the image
                    if ((x + dx != -1) && (x + dx != width) && (y + dy != -1) && (y + dy != height))
                    {
                        r += imagecp[y + dy][x + dx].rgbtRed;
                        g += imagecp[y + dy][x + dx].rgbtGreen;
                        b += imagecp[y + dy][x + dx].rgbtBlue;
                        no_avg++;
                    }
                }
            }

            //Converts pixel
            image[y][x].rgbtRed = round(r / (float) no_avg);
            image[y][x].rgbtGreen = round(g / (float) no_avg);
            image[y][x].rgbtBlue = round(b / (float) no_avg);
        }
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //Creates a reference image
    RGBTRIPLE imagecp[height][width];
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            imagecp[y][x] = image[y][x];
        }
    }
    
    //Kernels
    int gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            //Weighted sums [R, G, B]
            int x_wsum[3] = {0, 0, 0};
            int y_wsum[3] = {0, 0, 0};
            for (int dx = -1; dx <= 1; dx++)
            {
                for (int dy = -1; dy <= 1; dy++)
                {
                    //Checks if projected pixel is within the image
                    if ((x + dx != -1) && (x + dx != width) && (y + dy != -1) && (y + dy != height))
                    {
                        //Adds to weighted sums
                        x_wsum[0] += (imagecp[y + dy][x + dx].rgbtRed * gx[dy + 1][dx + 1]);
                        x_wsum[1] += (imagecp[y + dy][x + dx].rgbtGreen * gx[dy + 1][dx + 1]);
                        x_wsum[2] += (imagecp[y + dy][x + dx].rgbtBlue * gx[dy + 1][dx + 1]);
                        y_wsum[0] += (imagecp[y + dy][x + dx].rgbtRed * gy[dy + 1][dx + 1]);
                        y_wsum[1] += (imagecp[y + dy][x + dx].rgbtGreen * gy[dy + 1][dx + 1]);
                        y_wsum[2] += (imagecp[y + dy][x + dx].rgbtBlue * gy[dy + 1][dx + 1]);
                    }
                }
            }
            //Corrected colors
            int new_red = round(sqrt(pow(x_wsum[0], 2.0) + pow((y_wsum[0]), 2.0)));
            int new_green = round(sqrt(pow(x_wsum[1], 2.0) + pow((y_wsum[1]), 2.0)));
            int new_blue = round(sqrt(pow(x_wsum[2], 2.0) + pow((y_wsum[2]), 2.0)));
            
            //Adjusts image, capping at 255
            image[y][x].rgbtRed = (new_red <= 255) ? new_red : 255;
            image[y][x].rgbtGreen = (new_green <= 255) ? new_green : 255;
            image[y][x].rgbtBlue = (new_blue <= 255) ? new_blue : 255;
            
        }
    }
    return;
}
