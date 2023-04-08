#include "helpers.h"
#include "cs50.h"
#include <math.h>
#define MAX_RGB_VALUE 255
#define COLUMN_TO_LEFT -1
#define COLUMN_TO_RIGHT 1

#define RED_COLOR 0
#define GREEN_COLOR 1
#define BLUE_COLOR 2
 
void main()
{
// Convert image to grayscale
        void grayscale(int height, int width, RGBTRIPLE image[height][width])
        {
            for (int i = 0; i < width; i++)
            {
                for (int j = 0; j < height; j++)
                {
                    // averages the color and then apply the same value to all the colors to get gray image
                    int rgbGray = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

                    image[i][j].rgbtBlue = rgbGray;
                    image[i][j].rgbtGreen = rgbGray;
                    image[i][j].rgbtRed = rgbGray;
                }
            }
            return; 
        }





        // Convert image to sepia
        //give sepia formula
        //sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
        //sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
        //sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
    void sepia(int height, int width, RGBTRIPLE image[height][width])
    {
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                int sepiaRed = round((.393 * image[i][j].rgbtRed)  + (.769 * image[i][j].rgbtGreen) + (.189 * image[i][j].rgbtBlue));
                int sepiaGreen = round((.349 * image[i][j].rgbtRed) + (.686 *image[i][j].rgbtGreen) + (.168 * image[i][j].rgbtBlue));
                int sepiaBlue = round((.272 * image[i][j].rgbtRed) + (.534 * image[i][j].rgbtGreen) + (.131 * image[i][j].rgbtBlue));

                //since values can exceed 255 (bit counts) we have to cap such values at 255

                if(sepiaRed <= 255)
                {
                    image[i][j].rgbtRed = sepiaRed;
                }
                else
                {
                    image[i][j].rgbtRed = 255;
                }

                 if(sepiaGreen <= 255)
                {
                    image[i][j].rgbtGreen = sepiaGreen;
                }
                else
                {
                    image[i][j].rgbtGreen = 255;
                }

                 if(sepiaBlue <= 255)
                {
                    image[i][j].rgbtBlue = sepiaBlue;
                }
                else
                {
                    image[i][j].rgbtBlue = 255;
                }
            }
        }
        return;

    }

    // Reflect image horizontally
        void reflect(int height, int width, RGBTRIPLE image[height][width])
        {

            //here we have to reverse each rwo array to relect the image
            // we will swap each last or second last pixel with the first and the second pixel respectively 
            RGBTRIPLE temp;

        
            for (int i = 0; i < height; i++)
            {
            
                for (int j = 0; j < width / 2; j++)
                {
                    // Swaping
                    temp = image[i][j];
                    image[i][j] = image[i][width - j - 1];
                    image[i][width - j - 1] = temp;
                }
            }
            return;

        }    
    int getBlur( int i , int j, int height, int width,RGBTRIPLE image [height][width],int color_position )
    {
        float count = 0;
        int sum =0;
        for (int row = i -1; row <= (i+1); row++)
        {
            for(int column = j-1; column <= (j+1); column++)
            {
                if (row < 0 || row >= height|| column<0||column>= width)
                {
                    continue;
                }
                if (color_position == RED_COLOR)
                {
                    sum+=image[row][column].rgbtRed;
                }
                else if (color_position == GREEN_COLOR)
                {
                    sum+=image[row][column].rgbtGreen;
                }
                else (color_position == BLUE_COLOR)

                    sum+=image[row][column].rgbtBlue;
                
                    count++;
            }
        }
        return round(sum/count);
        
    }  
 
// Blur image
        void blur(int height, int width, RGBTRIPLE image[height][width])
        {
        RGBTRIPLE copy [height][width];
            for (int row = 0; row<height;row++)
            {
                for(int column = 0; column < width; column++)
                {
                    copy[row][column] = image[row][column];
                }
            
            }
            for(int row = 0; row< height;row++)
            {
                for(int column = 0; column< width; column++)
                {
                    image [row][column].rgbtRed=(row, column,height, width,copy ,RED_COLOR);
                    image [row][column].rgbtGreen=(row, column,height, width, copy ,GREEN_COLOR);
                    image [row][column].rgbtBlue=(row, column,height, width,copy ,BLUE_COLOR);
                }
            }
        }
    }