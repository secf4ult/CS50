#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#define key argv[1]
#define keylen strlen(argv[1])

int main(int argc, char* argv[])
{
    if ( argc != 2 || !isalpha(*argv[1]) )
    {
        printf ("Invalid Command.\n");
        return 1;
    }
    
    for (int i = 0; i < keylen; i++)
    {
        if (!isalpha(key[i]))
        {
            printf ("Invalid Key.\n");
            return 1;
        }
    }

    string p = GetString();

    for (int i = 0, j = 0, shift; i < strlen(p); i++)
    {
        if (isupper(key[j % keylen]))
            shift = key[j % keylen] - 65;
        else
            shift = key[j % keylen] - 97;

        if (isalpha(p[i]))
        {
            if (isupper(p[i]))
                p[i] = ((p[i] - 65 + shift) < 26)? p[i] + shift: (p[i] - 26 + shift);
            else if (islower(p[i]))
                p[i] = ((p[i] - 97 + shift) < 26)? p[i] + shift: (p[i] - 26 + shift);
            j++;
        }
    }
    printf("%s\n", p);

    return 0;
}