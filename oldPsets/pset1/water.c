#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("minutes: ");
    int s_time = GetInt();
    printf("bottles: %d\n", s_time * 12);
    return 0;
}