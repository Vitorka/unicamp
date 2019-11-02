#include <stdio.h>

/*BUSCA BIN*/
int main()
{
    int vetor[10], i, pos_fim, pos_ini, posmeio, pos, chave, parada = 0;
    
    for(i = 0; i < 10; i++)
    {
        scanf("%d", &vetor[i]);
    }
    
    scanf("%d", &chave);
    
    pos_ini = 1;
    pos_fim = 10;
    
    while((pos_ini <= pos_fim) && (parada == 0))
    {
        
        posmeio = (pos_fim + pos_ini) / 2;
        
        if(vetor[posmeio] == chave)
        {
            pos = posmeio;
            parada = 1;
        }   
        else if(chave < vetor[posmeio])
        {
            pos_fim = posmeio - 1;
        }
        else
        {
            pos_ini = posmeio + 1;
        }
    }
    
    printf("%d\n", pos);
    
    return 0;
}