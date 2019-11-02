#include <stdio.h>

/*void soma(int a, int b, int *c);*/

int main()
{
    int a[] = {1,2,3,4}, *b, i;
    
    b = a;
    
    for(i = 0; i < 4; i++)
    {
        printf("%d\n", b[i]);
    }

    return 0;
}

/*void soma(int a, int b, int *c)
{
    *c = a + b;
}*/