/* Nome: Vitor Kaoru Aoki
 * RA: 178474
 * Laboratorio 02 - Matrioshkas Generalizadas */

#include <stdlib.h>
#include <math.h>
#include "pilha.h"

/*Funcao que cria uma pilha adicionando o no cabeca*/
pilha *inicia_pilha(pilha *topo)
{
    pilha *new;
    
    new = malloc(sizeof(pilha));
    
    new->item = 0;
    new->capacidade = 0;
    new->prox = NULL;
    topo = new;
    
    return topo;
}

/*Funcao que adiciona os dados na pilha*/
pilha *cria_pilha(pilha *topo, int dado)
{
    pilha *new;
    
    new = malloc(sizeof(pilha));
    
    topo->capacidade -= fabs(dado);
    new->item = dado;
    new->capacidade = fabs(dado);
    new->prox = topo;
    topo = new;
    
    return topo;
}

/*Funcao que adiciona o primeiro elemento a pilha*/
pilha *primeiro_elemento(pilha *topo, int dado)
{
    pilha *new;
    
    new = malloc(sizeof(pilha));
    
    new->item = dado;
    new->capacidade = fabs(dado);
    new->prox = topo;
    topo = new;
    
    return topo;
}

/*Funcao que retira o elemento da pilha caso seja verificado que ele possui uma 
metade correspondente*/
pilha *retira(pilha *topo)
{
    pilha *aux;
    
    aux = topo;
    topo = topo->prox;
    free(aux);
    
    return topo;
}

/*Funcao que desaloca as pilhas criadas*/
void desaloca(pilha *topo)
{
    pilha *aux;
    
    for(aux = topo; topo != NULL; aux = topo)
    {
        topo = topo->prox;
        free(aux);
    }
    free(topo);
}