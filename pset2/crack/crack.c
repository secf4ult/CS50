#define _DOPEN_SOURCE
#include <unistd.h>

#include <stdio.h>
#include <string.h>

char *crypt(const char *key, const char *salt);
void setTheKey(char *string, char c, int bit);
int isFinished(char *key);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./crack hash\n");
        return 1;
    }

    // arguments
    const char *hash = argv[1];
    const char salt[3] = { hash[0], hash[1], '\0' };

    const char *password;
    // password no longer than 5 characters
    int count = 5;
    // firt iteration there's only one character
    char key[6] = { 'A', '\0', '\0', '\0', '\0', '\0'};

    // crack the code
    // for each time the password extend one byte
    int i = strlen(key);

    while (strlen(key) <= count)
    {
        // compare the key with iterate password
        if ( strcmp(hash, crypt(key, salt)) == 0)
        {
            password = key;
            break;
        }

        // when carry happens
        if (key[0] == 'z')
        {
            // i-bit key is max
            if ( isFinished(key) )
            {
                // extend the password and reset the key to all 'A'
                i++;
                setTheKey(key, 'A', strlen(key) + 1);
                continue;
            }
            else
            {
                // implement the carry
                for (int j = 1; j < strlen(key); j++)
                {
                    if (key[j] == 'Z')
                    {
                        key[j] = 'a' - 1;
                    }

                    // search for next carry bit
                    if (key[j] != 'z')
                    {
                        key[j]++;
                        setTheKey(key, 'A', j);
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        }
        // no carry
        else
        {
            // Z continues to a
            if (key[0] == 'Z')
            {
                key[0] = 'a' - 1;
            }

            key[0]++;
        }
    }

    printf("%s", password);
    printf("\n");

    return 0;
}

void setTheKey(char *key, char c, int n)
{
    // set the string to char c before n-th bit
    for (int i = 0; i < n; i++)
    {
        key[i] = c;
    }
}

int isFinished(char *key)
{
    for (int i = 0, n = strlen(key); i < n; i++)
    {
        if (key[i] != 'z')
        {
            return 0;
        }
    }

    return 1;
}