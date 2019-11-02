#include <stdio.h>

int main()
{
    int i, n;
    
    scanf("%d", &n);
    
    for(i = 0; i < 4; i++)
    {
        if((n & (1 << i)) == 0)
        {
            printf("bit%d\n", i);
            printf("%d\n\n", n & ( 1 << i));
        }
    }
    
    return 0;
}