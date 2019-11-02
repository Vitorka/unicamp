/* Nome: Vitor Kaoru Aoki
 * RA: 178474
 * Laboratorio 06 - Operações em ABB Auto-ajustáveis */

#include <stdio.h>
#include <stdlib.h>
#include "lab06.h"

int main()
{
    no *raiz = NULL;
    
    /*Cria a arvore*/
    raiz = cria_arvore(raiz);
    
    /*Realiza as operacoes dadas*/
    raiz = realiza_operacoes(raiz);
    
    printf("Pre-order :");
    pre_ordem(raiz);
    printf("\n");
    printf("In-order  :");
    inordem(raiz);
    printf("\n");
    desaloca(raiz);
    
    return 0;
}

