#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    int num_25, num_10, num_5, num_1;
    float c;

    do
    {
        printf("How many changes do you owe? ");
        c = GetFloat();
    }
    while (c <= 0);

    int cc =  round(c * 100.0);
    //printf("%d\n", cc);
    num_25 = cc / 25;
    num_10 = cc % 25 / 10;
    num_5  = cc % 25 % 10 / 5;
    num_1  = cc % 25 % 10 % 5;

    printf("%d\n", num_25 + num_10 + num_5 + num_1);

    return 0;
}
