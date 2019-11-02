#include <stdio.h>

int buscabin(int vetor[], int inic, int fim, int chave)
{
    int i, aux;
    
    if(chave > vetor[(inic + fim) / 2])
    {
        aux = buscabin(vetor, fim + 1, (fim + fim)/2, chave);
    }
    else if(chave < vetor[(inic + fim) / 2])
    {    
        aux = buscabin(vetor, inic, (inic + fim)/2, chave);
    }
    else if(chave == vetor[(inic + fim) / 2])
    {   
        for(i = 0; i < 10; i++)
        {
            if(chave == vetor[i])
            {
                return i;
            }
        }
    }
    
    return aux;
}

int main()
{
    int vetor[10];
    int i, aux, chave;
    
    for(i = 0; i < 10; i++)
    {
        scanf("%d", &vetor[i]);
    }
    
    scanf("%d", &chave);
    
    if(chave > vetor[10/2])
    {
        aux = buscabin(vetor, 10/2, 10, chave);
    }
    else if(chave < vetor[10/2])
    {

        aux = buscabin(vetor, 0, 10/2, chave);
    }
    else
    {
        aux = 10/2;
    }
    
    printf("%d\n", aux);
        
    return 0;
}
    