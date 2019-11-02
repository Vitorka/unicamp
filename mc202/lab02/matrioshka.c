/* Nome: Vitor Kaoru Aoki
 * RA: 178474
 * Laboratorio 02 - Matrioshkas Generalizadas */

#include "pilha.h"
#include <math.h>
#include <stdio.h>

/*Realiza os testes para verificar se o conjunto de numeros dados representam 
uma matrioshka através das especificacoes*/
pilha *matrioshkas(pilha *topo, int dado, int i, int *flag)
{
    if(dado < 0)
    {
        /*Adiciona o primeiro elemento a pilha*/
        if(i == 0)
        {
            topo = primeiro_elemento(topo, dado);
            *flag = 0;
            return topo;
        }
        /*Adiciona os proximos elementos a pilha, caso sejam menor ao elemento 
        que esta no topo e, caso a soma desse novo elemento com os elementos ja  
        presentes dentro do elemento mais externo, nao exceda nem iguale o 
        valor desse elemento mais externo. Verifica também se o brinquedo ja 
        foi finalizado. Caso ele ja tenha sido finalizado e outro elemento seja 
        inserido, nao representa uma matrioshka*/
        else if((fabs(dado) < fabs(topo->item)) && 
                (((topo->capacidade - fabs(dado)) > 0)) &&
                (topo->prox != NULL))
        {
            topo = cria_pilha(topo, dado);
            *flag = 0;
            return topo;
        }
        /*Caso nenhuma das condicoes sejam respeitas, os elementos nao 
        representam uma matrioshka*/
        else
        {
            *flag = 1;
            return topo;
        }
    }
    else
    {
        /*Verifica se o elemento positivo lido eh o primeiro elemento. Caso 
        seja, a sequencia dada nao representa uma matrioshka, pois nao existe o 
        elemento de abertura do brinquedo. E verifica, caso ele nao seja o 
        primeiro elemento, se ele representa o outra metade do elemento mais 
        externo*/    
        if((i != 0) && (dado == fabs(topo->item)))
        {
            topo = retira(topo);
            *flag = 0;
            return topo;
        }
        else
        {
            *flag = 1;
            return topo;
        }
    }
}