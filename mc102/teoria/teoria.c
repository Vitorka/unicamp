#include <stdio.h>

int mdc(int a, int b);

int main()
{
    int a, b, mdc2;
    
    scanf("%d %d", &a, &b);
    
    mdc2 = mdc(a, b);
    
    printf("O MDC entre %d e %d é: %d\n", a, b, mdc2);
    
    return 0;
}

int mdc(int a, int b)
{
    int c = 0, i, x;
    
    if(a > b)
    {    
        x = a;
    }
    else
    {
        x = b;
    }
    
    for(i = 1; i <= x; i++)
    {
        if((a % i == 0) && (b % i == 0) && (i > c))
        {
            c = i;
        }
    }
    return c;
}
    
    