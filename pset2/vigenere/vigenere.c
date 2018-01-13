#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

int isString(string s);
char vigenereShift(char c, char k);

int main(int argc, string argv[])
{
    // return 1 if it's not just one argument or the argument contains non-alphabetical character
    if (argc != 2 || !isString(argv[1]) )
    {
        printf("Usage: ./vigenere k\n");
        return 1;
    }

    // string k = argv[1]
    string k = argv[1];
    string p = get_string("plaintext:  ");

    // length of k and n
    int klen = strlen(k);
    int n = strlen(p);
    // counter for k
    int kCount = 0;

    for (int i = 0; i < n; i++)
    {
        // ignore non-alphabetical characters
        if ( isalpha(p[i]) )
        {
            p[i] = vigenereShift(p[i], k[kCount % klen]);
            kCount++;
        }
    }

    printf("ciphertext: %s", p);
    printf("\n");

    return 0;
}

int isString(string s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        if( !isalpha(s[i]) ) return false;
    }

    return true;
}

char vigenereShift(char c, char k)
{
    // transfer the k to the corresponding key
    if (isupper(k))
    {
        k = k - 'A';
    }
    else
    {
        k = k - 'a';
    }

    // Capitalized characters remain unchanged
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