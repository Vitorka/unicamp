#include <stdio.h>

/*INSERTION*/
int main()
{
    int vetor[6], i, j, aux, l;
    
    for(i = 0; i < 6; i++)
    {
        scanf("%d", &vetor[i]);
    }
    printf("\n");
    
    for(i = 1; i <= 6; i++)
    {
        l = i;
        for(j = i - 1; j >= 0; j--)
        {
            if(vetor[l] < vetor[j])
            {
                aux = vetor[j];
                vetor[j] = vetor[l];
                vetor[l] = aux;
                l = j;
            }
        }
    }
    
    for(i = 0; i < 6; i++)
    {
        printf("%d ", vetor[i]);
    }
    printf("\n");
    
    return 0;
}