#include <stdio.h>

/*BUSCA*/
int main()
{
    int vetor[10], i, chave, posicao = -1;
    
    for(i = 0; i < 10; i++)
    {
        scanf("%d", &vetor[i]);
    }
    
    scanf("%d", &chave);
    
    for(i = 0; i < 10; i++)
    {
        if(vetor[i] == chave)
        {
            posicao = i;
        }
    }
    
    printf("%d\n", posicao);
    
    return 0;
}