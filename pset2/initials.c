#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(void)
{
    string n = GetString();
    
    // print the first letter
    n[0] >= 'a' ? printf("%c", n[0] - 32) : printf("%c", n[0]);

    // print the rest letter
    for (int i = 0; i < strlen(n); i++)
    {
        if (n[i] == ' ')
        {
            n[i + 1] >= 'a' ? printf("%c", n[i + 1] - 32) : 
                              printf("%c", n[i + 1]);
        }
    }
    printf("\n");
    
    return 0;
}