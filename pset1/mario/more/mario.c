// Print out the bricks in trapezoid with given height

#include <stdio.h>
#include <cs50.h>

void printPyramid(int height);

int main(void)
{
    // prompt the user for a non-negative int no greater than 23
    int height;

    do
    {
        height = get_int("Input the height: ");
    }
    while (height > 23 || height < 0);

    // print the desired half-pyramids
    printPyramid(height);

    return 0;
}

void printPyramid(int height)
{
    int space = height - 1;
    int hashes = 1;

    // for each row in pyramid
    for (int i = 0; i < height; i++)
    {
        // print spaces
        for (int j = 0; j < space; j++)
        {
            printf(" ");
        }
        // printf left hashes
        for (int j = 0; j < hashes ; j++)
        {
            printf("#");
        }
        // print gaps
        printf("  ");
        // printf right hashes
        for (int j = 0; j < hashes; j++)
        {
            printf("#");
        }
        space--;
        hashes++;
        printf("\n");
    }
}