#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>

int main(int argc, char* argv[])
{
    if (argc > 2 || argc < 2)
    {
        printf ("Invalid Key.");
        return 1;
    }
        
    string t = GetString();
    int k = atoi(argv[1]) % 26;

    for (int i = 0, n = strlen(t); i < n; i++)
    {
        if (t[i] >= 'A' && t[i] <= 'Z')
        {
            if (t[i] - 64 + k > 26)
                t[i] -= (26 - k);
            else
                t[i] += k;
        }
        else if (t[i] >= 'a' && t[i] <= 'z')
        {
            if (t[i] - 96 + k > 26)
                t[i] -= (26 - k);
            else
                t[i] += k;
        }
    }
    
    printf("%s\n", t);
    
    return 0;
}