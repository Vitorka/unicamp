#include <stdio.h>

void mdc(int num1, int num2);

int main()
{
    int num1, num2;
    
    printf("Entre com dois numeros: ");
    
    scanf("%d %d", &num1, &num2);
    
    mdc(num1, num2);
    
    return 0;
}

void mdc(int num1, int num2)
{
    int i, x, maior;
    
    if(num1 > num2)
    {
        x = num1;
    }
    else
    {
        x = num2;
    }
    
    for(i = 1; i <= x; i++)
    {
        if((num1 % i == 0) && (num2 % i == 0))
        {
            maior = i;
        }   
    }
    
    printf("MDC = %d\n", maior);
}