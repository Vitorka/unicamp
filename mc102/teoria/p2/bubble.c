#include <stdio.h>

/*BUBBLE*/
int main()
{
    int i, vetor[6], aux, j;
    
    for(i = 0; i < 6; i++)
    {
        scanf("%d", &vetor[i]);
    }
    
    for(j = 0; j < 6; j++)
    {
        for(i = 0; i < 6; i++)
        {
            if(vetor[i] > vetor[i + 1])
            {
                aux = vetor[i];
                vetor[i] = vetor[i + 1];
                vetor[i + 1] = aux;
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