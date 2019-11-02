#include <stdio.h>
#include <stdlib.h>

int main()
{
    char *a, *b;
    int tamvet, i, *vet, *vet2, tamvet2, j, result[1000], flag = 0, k, contador;
    
    scanf("%d", &tamvet);
    scanf("%d", &tamvet2);
    a = malloc(tamvet * sizeof(char));
    vet = malloc(tamvet * sizeof(int));
    b = malloc(tamvet2 * sizeof(char));
    vet2 = malloc(tamvet2 * sizeof(int));
    
    /*Le as strings com os numeros*/
    scanf(" ");
    for(i = tamvet - 1; i >= 0; i--)
    {
        scanf("%c", &a[i]);
        vet[i] = a[i] - '0';
    }
    scanf(" ");
    for(i = tamvet2 - 1; i >= 0; i--)
    {
        scanf("%c", &b[i]);
        vet2[i] = b[i] - '0';
    }
    
    /*Operacao de multiplicacao*/
    for(i = 0; i < tamvet2; i++)
    {
        for(j = 0, n = 1; j < tamvet; j++, n *= 10)
        {
            if((vet2[i] * vet[j]) >= 10)
            {
                vet[j + 1] += (vet2[i] * vet[j]) / 10;
                result[i] += ((vet2[i] * vet[j]) % 10) * n;
            }
            else
            {
                result[i] += ((vet2[i] * vet[j]) % 10) * n;
            }
        }
    }
            
    
    /*Imprimi cada string e cada vetor de numeros*/
    for(i = tamvet - 1; i >= 0; i--)
    {
        printf("%d", result[i]);
    }
    printf("\n");
        
    return 0;
}