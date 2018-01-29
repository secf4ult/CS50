// check if the credit card number is valid

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    long long number;
    long long numberCpy;
    int checksum = 0;

    // get the credit card number
    do
    {
        number = numberCpy = get_long_long("Number: ");
    }
    while (number <= 0);

    // calculate the checksum
    int i = 0;
    while (number > 1)
    {
        int sum = 0;

        if (i % 2 == 1)
        {
            // multiply every other digit by 2 starting with the penultimate digit
            sum = number % 10 * 2;
            if (sum >= 10)
            {
                sum = sum / 10 + sum % 10;
            }
        }
        else
        {
            // add the sum to the sum of the digits that weren't multiplied by 2
            sum = number % 10;
        }
        checksum += sum;
        number /= 10;

        i++;
    }

    // check the checksum
    if (checksum % 10 == 0)
    {
        // check the head numbers
        while (numberCpy > 10)
        {
            numberCpy /= 10;
        }

        switch (numberCpy)
        {
            case 3:
                printf("AMEX\n");
                break;
            case 5:
                printf("MASTERCARD\n");
                break;
            case 4:
                printf("VISA\n");
                break;
        }
    }
    else
    {
        printf("INVALID\n");
    }

    return 0;
}