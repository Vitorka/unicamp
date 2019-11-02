/* Nome: Vitor Kaoru Aoki
 * RA: 178474
 * Laboratorio 02 - Matrioshkas Generalizadas */

#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
#include "matrioshka.h"

int main()
{
    int i, tamanho, dado, flag = 0;
    pilha *topo = NULL;
    
    scanf("%d", &tamanho);
    
    /*Le todas as entradas dadas e realiza o teste se eh ou nao uma matrioshka*/
    while(tamanho != 0)
    {
        topo = inicia_pilha(topo);
        
        for(i = 0; i < tamanho; i++)
        {
            scanf("%d", &dado);
            
            /*Caso a flag seja 0, os numeros dados representam uma matrioshka, 
            caso ele seja 1, os numeros nao representam uma matrioshka*/
            if(flag == 0)
            {
                topo = matrioshkas(topo, dado, i, &flag);
            }
        }
        
        if(flag == 0)
        {
            printf("Eh Matrioshka.\n");
        }
        else
        {
            printf("Nao eh Matrioshka.\n");
        }
        
        desaloca(topo);
        scanf("%d", &tamanho);
        flag = 0;
    }
   
    return 0;
}






