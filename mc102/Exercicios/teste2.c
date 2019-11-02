/*Nome: Vitor Aoki
  RA: 178474
*/  

#include <stdio.h>

int main()
{
    /*Teste para identificar se as medidas formam um trinângulo*/
    
    int a, b, c;
    
    printf("De tres medidas de lados: ");
    scanf("%d %d %d", &a, &b, &c);
    
    if (((a + b) >= c) && ((c + a) >= b) && ((b + c) >= a))
    {
        printf("As medidas fornecidas formam um triangulo\n");
        
        if ((a == b) && (b == c))
        {
            printf("O triangulo eh equilatero\n");
        }
        
        if ((a == b) || (b == c) || (a == c))
        {
            printf("O triangulo eh isoceles\n");
        }
        
        if ((a != b) && (a != c) && (b != c))
        {
            printf("O triangulo eh escaleno\n");
        }    
        
        if (((a * a) == (b * b) + (c * c)) || ((b * b) == (a * a) + (c * c)) || 
           ((c * c) == (a * a) + (b * b)))
        {
            printf("O triangulo eh retangulo\n");
        }    
        
    }
    
    else 
    {
        printf("As medidas fornecidas nao formam um triangulo\n");
    }

    return 0;
}
            