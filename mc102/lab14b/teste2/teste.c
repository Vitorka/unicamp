#include <stdio.h> 
#include <stdlib.h>

void combinacao_simples(int n, int r, int temp[],
                        int next, int size);

void imprime_vetor(int vetor[], int n) 
{
    int i;
    
    for (i = 0; i < n; i++)
    {
        printf("%d ", vetor[i] + 1);
    }
    printf("\n");
}

int main() 
{
    int n, r, *temp;
    
    printf("Entre com o valor de n: ");
    scanf("%d", &n);
    
    printf("Entre com o valor de r: ");
    scanf("%d", &r);
    
    temp = malloc(r * sizeof(int));
    
    while(r != 0)
    {
        combinacao_simples(n, r, temp, 0, 0);
        r--;
    }
    
    free(temp);
    
    return 0;
}

void combinacao_simples(int n, int r, int temp[],
                        int next, int size) 
{
    int i;
    
    if (size == r)
    {
        imprime_vetor(temp, r);
    }
    else
    {
        for (i = next; i < n; i++) 
        {
            temp[size] = i;
            combinacao_simples(n, r, temp, i + 1, size + 1);
        }
    }
}