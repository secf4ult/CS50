#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

char caesarShift(char c, int k);

int main(int argc, string argv[])
{
    // return 1 if there's more than one argument.
    if (argc != 2)
    {
        printf("Usage: ./caesar k\n");
        return 1;
    }

    // remainder of k
    int k = atoi(argv[1]) % 26;
    string p = get_string("plaintext:  ");

    // shift the character
    for (int i = 0, n = strlen(p); i < n; i++)
    {
        if (isalpha(p[i]))
        {
            p[i] = caesarShift(p[i], k);
        }
    }

    printf("ciphertext: %s", p);
    printf("\n");

    return 0;
}

char caesarShift(char c, int k)
{
    // non-alphabetical characters remain unchanged.

    // Capitalized characters remain unchanged.
    if (isupper(c))
    {
        c = ((c - 'A') + k) % 26 + 'A';
    }
    else
    {
        c = ((c - 'a') + k) % 26 + 'a';
    }

    return c;
}