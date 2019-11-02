/* Nome: Vitor Kaoru Aoki 
 * RA: 178474    
 * Laboratorio 05 - Pré, In e Pós */

#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main()
{
    int i, num_testes, num_nos;
    char *in_ordem, *pre_ordem;
    no *raiz = NULL;
    
    scanf("%d", &num_testes);
    
    /*Executa todos os casos de teste dados na entrada*/
    for(i = 0; i < num_testes; i++)
    {
        scanf("%d", &num_nos);
        
        pre_ordem = malloc(num_nos * sizeof(char));
        in_ordem = malloc(num_nos * sizeof(char));
        
        /*Le o percurso em pre-ordem*/
        le_percurso(pre_ordem, num_nos);
        
        /*Le o percurso em in-ordem*/
        le_percurso(in_ordem, num_nos);
        
        /*Monta a arvore a partir dos percursos em per-ordem e in-ordem*/
        raiz = monta_arvore(pre_ordem, in_ordem, num_nos, 0, 0, num_nos);
        
        printf("Teste %d: ", i);
        imprime_pos_ordem(raiz); 
        printf("\n");
        
        free(pre_ordem);
        free(in_ordem);
        desaloca(raiz);
    }
    
    return 0;
}
            
    
    
       
        
            