#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            BYTE originalRed = image[i][k].rgbtRed;
            BYTE originalGreen = image[i][k].rgbtGreen;
            BYTE originalBlue = image[i][k].rgbtBlue;

            WORD total = originalRed + originalGreen + originalBlue;

            BYTE avg = round((float)total/3);

            image[i][k].rgbtRed = avg;
            image[i][k].rgbtGreen = avg;
            image[i][k].rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
     // go through the image array and turn each triple into a new triple based on the formulas
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            BYTE originalRed = image[i][k].rgbtRed;
            BYTE originalGreen = image[i][k].rgbtGreen;
            BYTE originalBlue = image[i][k].rgbtBlue;

            WORD tRed = round((float)(.393 * (float)originalRed + .769 * (float)originalGreen + .189 * (float)originalBlue));
            WORD tGreen = round((float)(.349 * (float)originalRed + .686 * (float)originalGreen + .168 * (float)originalBlue));
            WORD tBlue = round((float)(.272 * (float)originalRed + .534 * (float)originalGreen + .131 * (float)originalBlue));


            image[i][k].rgbtRed = (BYTE)(tRed > 255? 255: tRed);
            image[i][k].rgbtGreen = (BYTE)(tGreen > 255? 255: tGreen);
            image[i][k].rgbtBlue = (BYTE)(tBlue > 255? 255: tBlue);
        }
    }

    return;
}

void swap(BYTE* a, BYTE* b)
{
    BYTE tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void test_swap(int height, int width, RGBTRIPLE image[height][width])
{
    int k = 0, i = 0;
    BYTE a, b;

    a = 200;
    b = 55;

    swap(&a, &b);
    printf("%i, %i\n", a, b);
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
     for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width/2; k++)
        {
            swap(&(image[i][k].rgbtRed), &(image[i][width-k-1].rgbtRed));
            swap(&(image[i][k].rgbtGreen), &(image[i][width-k-1].rgbtGreen));
            swap(&(image[i][k].rgbtBlue), &(image[i][width-k-1].rgbtBlue));
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE newImage[height][width]; //Because we can't modify the original

    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            WORD totalR = 0, totalG = 0, totalB = 0;

            // For most pixels, all 9 surrounding are available
            if((i>0 && i<height-1) && (k>0 && k<width-1))
            {
                BYTE Red2 = image[i-1][k-1].rgbtRed;
                BYTE Green2 = image[i-1][k-1].rgbtGreen;
                BYTE Blue2 = image[i-1][k-1].rgbtBlue;

                BYTE Red3 = image[i-1][k].rgbtRed;
                BYTE Green3 = image[i-1][k].rgbtGreen;
                BYTE Blue3 = image[i-1][k].rgbtBlue;

                BYTE Red4 = image[i-1][k+1].rgbtRed;
                BYTE Green4 = image[i-1][k+1].rgbtGreen;
                BYTE Blue4 = image[i-1][k+1].rgbtBlue;

                BYTE Red5 = image[i][k-1].rgbtRed;
                BYTE Green5 = image[i][k-1].rgbtGreen;
                BYTE Blue5 = image[i][k-1].rgbtBlue;

                BYTE Red1 = image[i][k].rgbtRed;
                BYTE Green1 = image[i][k].rgbtGreen;
                BYTE Blue1 = image[i][k].rgbtBlue;


                BYTE Red6 = image[i][k+1].rgbtRed;
                BYTE Green6 = image[i][k+1].rgbtGreen;
                BYTE Blue6 = image[i][k+1].rgbtBlue;

                BYTE Red7 = image[i+1][k-1].rgbtRed;
                BYTE Green7 = image[i+1][k-1].rgbtGreen;
                BYTE Blue7 = image[i+1][k-1].rgbtBlue;

                BYTE Red8 = image[i+1][k].rgbtRed;
                BYTE Green8 = image[i+1][k].rgbtGreen;
                BYTE Blue8 = image[i+1][k].rgbtBlue;

                BYTE Red9 = image[i+1][k+1].rgbtRed;
                BYTE Green9 = image[i+1][k+1].rgbtGreen;
                BYTE Blue9 = image[i+1][k+1].rgbtBlue;


                totalR = Red1 + Red2 + Red3 + Red4 + Red5 + Red6 + Red7 + Red8 + Red9;
                totalG = Green1 + Green2 + Green3 + Green4 + Green5 + Green6 + Green7 + Green8 + Green9;
                totalB = Blue1 + Blue2 + Blue3 + Blue4 + Blue5 + Blue6 + Blue7 + Blue8 + Blue9;

                BYTE avgR = round((float)totalR/9);
                BYTE avgG = round((float)totalG/9);
                BYTE avgB = round((float)totalB/9);

                newImage[i][k].rgbtRed = avgR;
                newImage[i][k].rgbtGreen = avgG;
                newImage[i][k].rgbtBlue = avgB;

            }


            // Each edge

            else if (i == 0)
            {

                // Each of the corners have 4*4 matrices - this row has two
                if (k == 0) // top left
                {
                    BYTE Red1 = image[i][k].rgbtRed;
                    BYTE Green1 = image[i][k].rgbtGreen;
                    BYTE Blue1 = image[i][k].rgbtBlue;


                    BYTE Red6 = image[i][k+1].rgbtRed;
                    BYTE Green6 = image[i][k+1].rgbtGreen;
                    BYTE Blue6 = image[i][k+1].rgbtBlue;

                    BYTE Red8 = image[i+1][k].rgbtRed;
                    BYTE Green8 = image[i+1][k].rgbtGreen;
                    BYTE Blue8 = image[i+1][k].rgbtBlue;

                    BYTE Red9 = image[i+1][k+1].rgbtRed;
                    BYTE Green9 = image[i+1][k+1].rgbtGreen;
                    BYTE Blue9 = image[i+1][k+1].rgbtBlue;


                    totalR = Red1 + Red6 + Red8 + Red9;
                    totalG = Green1 + Green6 + Green8 + Green9;
                    totalB = Blue1 + Blue6 + Blue8 + Blue9;

                    BYTE avgR = round((float)totalR/4);
                    BYTE avgG = round((float)totalG/4);
                    BYTE avgB = round((float)totalB/4);

                    newImage[i][k].rgbtRed = avgR;
                    newImage[i][k].rgbtGreen = avgG;
                    newImage[i][k].rgbtBlue = avgB;

                }

                else if (k == width-1)      //top right
                {
                    BYTE Red1 = image[i][k].rgbtRed;
                    BYTE Green1 = image[i][k].rgbtGreen;
                    BYTE Blue1 = image[i][k].rgbtBlue;


                    BYTE Red6 = image[i][k-1].rgbtRed;
                    BYTE Green6 = image[i][k-1].rgbtGreen;
                    BYTE Blue6 = image[i][k-1].rgbtBlue;

                    BYTE Red8 = image[i+1][k].rgbtRed;
                    BYTE Green8 = image[i+1][k].rgbtGreen;
                    BYTE Blue8 = image[i+1][k].rgbtBlue;

                    BYTE Red9 = image[i+1][k-1].rgbtRed;
                    BYTE Green9 = image[i+1][k-1].rgbtGreen;
                    BYTE Blue9 = image[i+1][k-1].rgbtBlue;


                    totalR = Red1 + Red6 + Red8 + Red9;
                    totalG = Green1 + Green6 + Green8 + Green9;
                    totalB = Blue1 + Blue6 + Blue8 + Blue9;

                    BYTE avgR = round((float)totalR/4);
                    BYTE avgG = round((float)totalG/4);
                    BYTE avgB = round((float)totalB/4);

                    newImage[i][k].rgbtRed = avgR;
                    newImage[i][k].rgbtGreen = avgG;
                    newImage[i][k].rgbtBlue = avgB;

                }

                else
                {
                    BYTE Red1 = image[i][k].rgbtRed;
                    BYTE Green1 = image[i][k].rgbtGreen;
                    BYTE Blue1 = image[i][k].rgbtBlue;

                    BYTE Red2 = image[i][k-1].rgbtRed;
                    BYTE Green2 = image[i][k-1].rgbtGreen;
                    BYTE Blue2 = image[i][k-1].rgbtBlue;

                    BYTE Red6 = image[i][k+1].rgbtRed;
                    BYTE Green6 = image[i][k+1].rgbtGreen;
                    BYTE Blue6 = image[i][k+1].rgbtBlue;

                    BYTE Red3 = image[i+1][k-1].rgbtRed;
                    BYTE Green3 = image[i+1][k-1].rgbtGreen;
                    BYTE Blue3 = image[i+1][k-1].rgbtBlue;

                    BYTE Red8 = image[i+1][k].rgbtRed;
                    BYTE Green8 = image[i+1][k].rgbtGreen;
                    BYTE Blue8 = image[i+1][k].rgbtBlue;

                    BYTE Red9 = image[i+1][k+1].rgbtRed;
                    BYTE Green9 = image[i+1][k+1].rgbtGreen;
                    BYTE Blue9 = image[i+1][k+1].rgbtBlue;


                    totalR = Red1 + Red6 + Red8 + Red9 + Red2 + Red3;
                    totalG = Green1 + Green6 + Green8 + Green9 + Green2 + Green3;
                    totalB = Blue1 + Blue6 + Blue8 + Blue9 + Blue2 + Blue3;

                    BYTE avgR = round((float)totalR/6);
                    BYTE avgG = round((float)totalG/6);
                    BYTE avgB = round((float)totalB/6);

                    newImage[i][k].rgbtRed = avgR;
                    newImage[i][k].rgbtGreen = avgG;
                    newImage[i][k].rgbtBlue = avgB;

                }

            } // end i == 0, i.e. top row

            else if (i == height-1)
            {
                //bottom right
                if (k == width-1)
                {
                    BYTE Red1 = image[i][k].rgbtRed;
                    BYTE Green1 = image[i][k].rgbtGreen;
                    BYTE Blue1 = image[i][k].rgbtBlue;


                    BYTE Red6 = image[i][k-1].rgbtRed;
                    BYTE Green6 = image[i][k-1].rgbtGreen;
                    BYTE Blue6 = image[i][k-1].rgbtBlue;

                    BYTE Red8 = image[i-1][k].rgbtRed;
                    BYTE Green8 = image[i-1][k].rgbtGreen;
                    BYTE Blue8 = image[i-1][k].rgbtBlue;

                    BYTE Red9 = image[i-1][k-1].rgbtRed;
                    BYTE Green9 = image[i-1][k-1].rgbtGreen;
                    BYTE Blue9 = image[i-1][k-1].rgbtBlue;


                    totalR = Red1 + Red6 + Red8 + Red9;
                    totalG = Green1 + Green6 + Green8 + Green9;
                    totalB = Blue1 + Blue6 + Blue8 + Blue9;

                    BYTE avgR = round((float)totalR/4);
                    BYTE avgG = round((float)totalG/4);
                    BYTE avgB = round((float)totalB/4);

                    newImage[i][k].rgbtRed = avgR;
                    newImage[i][k].rgbtGreen = avgG;
                    newImage[i][k].rgbtBlue = avgB;

                }

                // bottom left
                else if (k == 0)
                {
                    BYTE Red1 = image[i][k].rgbtRed;
                    BYTE Green1 = image[i][k].rgbtGreen;
                    BYTE Blue1 = image[i][k].rgbtBlue;

                    BYTE Red6 = image[i][k+1].rgbtRed;
                    BYTE Green6 = image[i][k+1].rgbtGreen;
                    BYTE Blue6 = image[i][k+1].rgbtBlue;

                    BYTE Red8 = image[i-1][k].rgbtRed;
                    BYTE Green8 = image[i-1][k].rgbtGreen;
                    BYTE Blue8 = image[i-1][k].rgbtBlue;

                    BYTE Red9 = image[i-1][k+1].rgbtRed;
                    BYTE Green9 = image[i-1][k+1].rgbtGreen;
                    BYTE Blue9 = image[i-1][k+1].rgbtBlue;


                    totalR = Red1 + Red6 + Red8 + Red9;
                    totalG = Green1 + Green6 + Green8 + Green9;
                    totalB = Blue1 + Blue6 + Blue8 + Blue9;

                    BYTE avgR = round((float)totalR/4);
                    BYTE avgG = round((float)totalG/4);
                    BYTE avgB = round((float)totalB/4);

                    newImage[i][k].rgbtRed = avgR;
                    newImage[i][k].rgbtGreen = avgG;
                    newImage[i][k].rgbtBlue = avgB;

                }
                else
                {
                    BYTE Red1 = image[i][k].rgbtRed;
                    BYTE Green1 = image[i][k].rgbtGreen;
                    BYTE Blue1 = image[i][k].rgbtBlue;

                    BYTE Red2 = image[i][k-1].rgbtRed;
                    BYTE Green2 = image[i][k-1].rgbtGreen;
                    BYTE Blue2 = image[i][k-1].rgbtBlue;

                    BYTE Red6 = image[i][k+1].rgbtRed;
                    BYTE Green6 = image[i][k+1].rgbtGreen;
                    BYTE Blue6 = image[i][k+1].rgbtBlue;

                    BYTE Red3 = image[i-1][k-1].rgbtRed;
                    BYTE Green3 = image[i-1][k-1].rgbtGreen;
                    BYTE Blue3 = image[i-1][k-1].rgbtBlue;

                    BYTE Red8 = image[i-1][k].rgbtRed;
                    BYTE Green8 = image[i-1][k].rgbtGreen;
                    BYTE Blue8 = image[i-1][k].rgbtBlue;

                    BYTE Red9 = image[i-1][k+1].rgbtRed;
                    BYTE Green9 = image[i-1][k+1].rgbtGreen;
                    BYTE Blue9 = image[i-1][k+1].rgbtBlue;

                    totalR = Red1 + Red6 + Red8 + Red9 + Red2 + Red3;
                    totalG = Green1 + Green6 + Green8 + Green9 + Green2 + Green3;
                    totalB = Blue1 + Blue6 + Blue8 + Blue9 + Blue2 + Blue3;

                    BYTE avgR = round((float)totalR/6);
                    BYTE avgG = round((float)totalG/6);
                    BYTE avgB = round((float)totalB/6);

                    newImage[i][k].rgbtRed = avgR;
                    newImage[i][k].rgbtGreen = avgG;
                    newImage[i][k].rgbtBlue = avgB;

                }

            }   // end if bottom row

            else if (k==0)  //left column
            {
                    BYTE Red1 = image[i][k].rgbtRed;
                    BYTE Green1 = image[i][k].rgbtGreen;
                    BYTE Blue1 = image[i][k].rgbtBlue;

                    BYTE Red2 = image[i][k+1].rgbtRed;
                    BYTE Green2 = image[i][k+1].rgbtGreen;
                    BYTE Blue2 = image[i][k+1].rgbtBlue;

                    BYTE Red6 = image[i+1][k+1].rgbtRed;
                    BYTE Green6 = image[i+1][k+1].rgbtGreen;
                    BYTE Blue6 = image[i+1][k+1].rgbtBlue;

                    BYTE Red3 = image[i+1][k].rgbtRed;
                    BYTE Green3 = image[i+1][k].rgbtGreen;
                    BYTE Blue3 = image[i+1][k].rgbtBlue;

                    BYTE Red8 = image[i-1][k].rgbtRed;
                    BYTE Green8 = image[i-1][k].rgbtGreen;
                    BYTE Blue8 = image[i-1][k].rgbtBlue;

                    BYTE Red9 = image[i-1][k+1].rgbtRed;
                    BYTE Green9 = image[i-1][k+1].rgbtGreen;
                    BYTE Blue9 = image[i-1][k+1].rgbtBlue;

                    totalR = Red1 + Red6 + Red8 + Red9 + Red2 + Red3;
                    totalG = Green1 + Green6 + Green8 + Green9 + Green2 + Green3;
                    totalB = Blue1 + Blue6 + Blue8 + Blue9 + Blue2 + Blue3;

                    BYTE avgR = round((float)totalR/6);
                    BYTE avgG = round((float)totalG/6);
                    BYTE avgB = round((float)totalB/6);

                    newImage[i][k].rgbtRed = avgR;
                    newImage[i][k].rgbtGreen = avgG;
                    newImage[i][k].rgbtBlue = avgB;

            }
            else if (k==height-1)
            {
                    BYTE Red1 = image[i][k].rgbtRed;
                    BYTE Green1 = image[i][k].rgbtGreen;
                    BYTE Blue1 = image[i][k].rgbtBlue;

                    BYTE Red2 = image[i][k-1].rgbtRed;
                    BYTE Green2 = image[i][k-1].rgbtGreen;
                    BYTE Blue2 = image[i][k-1].rgbtBlue;

                    BYTE Red6 = image[i+1][k].rgbtRed;
                    BYTE Green6 = image[i+1][k].rgbtGreen;
                    BYTE Blue6 = image[i+1][k].rgbtBlue;

                    BYTE Red3 = image[i+1][k-1].rgbtRed;
                    BYTE Green3 = image[i+1][k-1].rgbtGreen;
                    BYTE Blue3 = image[i+1][k-1].rgbtBlue;

                    BYTE Red8 = image[i-1][k].rgbtRed;
                    BYTE Green8 = image[i-1][k].rgbtGreen;
                    BYTE Blue8 = image[i-1][k].rgbtBlue;

                    BYTE Red9 = image[i-1][k-1].rgbtRed;
                    BYTE Green9 = image[i-1][k-1].rgbtGreen;
                    BYTE Blue9 = image[i-1][k-1].rgbtBlue;

                    totalR = Red1 + Red6 + Red8 + Red9 + Red2 + Red3;
                    totalG = Green1 + Green6 + Green8 + Green9 + Green2 + Green3;
                    totalB = Blue1 + Blue6 + Blue8 + Blue9 + Blue2 + Blue3;

                    BYTE avgR = round((float)totalR/6);
                    BYTE avgG = round((float)totalG/6);
                    BYTE avgB = round((float)totalB/6);

                    newImage[i][k].rgbtRed = avgR;
                    newImage[i][k].rgbtGreen = avgG;
                    newImage[i][k].rgbtBlue = avgB;

            }
        }
    }

    // Need to copy the new to old...
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            image[i][k] = newImage[i][k];
        }
    }
    return;
}
