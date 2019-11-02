/* Nome: Vitor Kaoru Aoki
 * RA: 178474
 * Laboratorio 06 - Operações em ABB Auto-ajustáveis */

#include <stdio.h>
#include <stdlib.h>
#include "lab06.h"

int main()
{
    int num_elem, elemento;
    no *raiz = NULL;
    
    scanf("%d", &num_elem);
    scanf("%d", &elemento);
    
    /*Inicializa a arvore, adicionando o no raiz*/
    raiz = insere_no(elemento, NULL);
    raiz = cria_arvore(num_elem, raiz);
    
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

