#include <stdio.h>
#include <math.h>

int main()
{
    int pos;
    double vel;
    int i;
    
    scanf("%d", &pos);
    
    vel = (10 * pos)/2;
    
    for(i = 0; i < 10; i++)
    {
        vel = (vel + ((10 * pos) / vel))/2;
    }
    
    printf("%f\n", vel);
    
    return 0;
}
