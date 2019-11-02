#include <stdio.h>

int percorre(int bolas, int no_atual, int profundidade);

int main()
{
    int i, num_testes, profundidade, bolas, final;
    
    scanf("%d", &num_testes);
    
    for(i = 0; i < num_testes; i++)
    {
        scanf("%d %d", &profundidade, &bolas);
        
        final = percorre(bolas, 1, profundidade);
        printf("%d\n", final);
    }
    
    return 0;
}

int percorre(int bolas, int no_atual, int profundidade)
{
    if(profundidade == 1)
    {
        return no_atual;
    }
    else
    {
        if(bolas % 2) /*Impar - esquerda*/
        {
            return percorre((bolas + 1) / 2, (no_atual * 2), profundidade - 1);
        }
        else /*Par - direita*/
        {
            return percorre(bolas / 2, ((no_atual * 2) + 1), profundidade - 1);
        }
    }
}