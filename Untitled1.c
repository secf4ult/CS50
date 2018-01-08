#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    double f1, f2, f3, epsilon, delta = 3000;
    
    // f1 f2 f3
    printf("input f1 f2 f3: ");
    scanf("%lf %lf %lf\n", &f1, &f2, &f3);
    
    // epsilon
    printf("input epsilon: ");
    scanf("%lf\n", &epsilon);
    
    f1 = 9.89E-4 * (756.9787 - 0.06111 * delta ) + 3.9395E-5 * ( 1917.247 - 0.1667 * delta );
    f2 = 1.0872E-5 * ( 7812.355 + 0.06111 * delta ) - 0.011597 + 4.1304E-6 * ( 8888.9 + 0.16667 * delta );
    f3 = 3.1434E-5 * delta;
    
    while( f1 - f2 - f3 > epsilon )
    {
        if ( f1 - f2 - f3 < 0 )
        {
            delta -= 0.1;
        }
        else
        {
            delta += 0.1;
        }
    }
    
    printf("%lf %lf\n", &f1, &delta);
    
    return 0;
}