#include <stdio.h>

/*SELECTION*/
int main()
{
    int i, vetor[6], j, k, aux;
    
    for(i = 0; i < 6; i++)
    {
        scanf("%d", &vetor[i]);
    }
    
    for(i = 0; i < 6; i++)
    {
        k = i;
        
        for(j = i + 1; j < 6; j++)
        {
            if(vetor[k] < vetor[j])
            {
                k = j;
            }
        }
        
        aux = vetor[i];
        vetor[i] = vetor[k];
        vetor[k] = aux;
        
    }
    
    for(i = 0; i < 6; i++)
    {
        printf("%d ", vetor[i]);
    }
    printf("\n");
    
    return 0;
}