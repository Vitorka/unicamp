/* Nome: Vitor Kaoru Aoki 
 * RA: 178474 
 * Laboratorio 04 - Soltando bolas em uma árvore */

#include <stdio.h>
#include <stdlib.h>
#include "lab04.h"
#define true 1
#define false 0

/*Funcao que inicia a arvore com o apontador para a raiz*/
arv_bin *inicia_arvore(int profundidade)
{
    arv_bin *new;
    
    new = malloc(sizeof(arv_bin));
    
    new->prof = profundidade;
    new->raiz = NULL;
    
    return new;
}

/*Funcao que insere um novo no, com seu respectivo valor, na arvore*/
no *insere_no(int posicao)
{
    no *new;
    
    new = malloc(sizeof(no));
    
    new->item = posicao;
    new->flag = false;
    new->esq = NULL;
    new->dir = NULL;
    
    return new;
}

/*Funcao que cria a arvore. Inicialmente a variavel profundidade possui o 
valor inicial dado como entrada. A medida que os nos vao sendo criados, essa 
variavel vai diminuindo de valor, ate atingir o valor do penultimo nivel, 
quando o ultimo nivel de nos eh criado*/
void cria_arvore(no *no_atual, int posicao, int profundidade)
{       
    /*Insere o no a esquerda*/
    no_atual->esq = insere_no(posicao *  2);
    
    /*Insere o no a direita*/
    no_atual->dir = insere_no(((posicao * 2) + 1));
    
    /*Continua inserindo nos na arvore, caso todos os niveis ainda nao estejam 
    completos*/
    if(profundidade > 2)
    {
        cria_arvore(no_atual->esq, posicao * 2, profundidade - 1);
        cria_arvore(no_atual->dir, ((posicao * 2) + 1), profundidade - 1);
    }
}

/*Funca que percorre a arvore, realizando o percurso seguido pela bola*/
int percurso_bola(no *no_atual)
{
    int no_final;
    
    /*Caso a bola chegue no ultimo no da arvore, retorna a posicao em que ela 
    se enontra*/
    if((no_atual->dir == NULL) && (no_atual->esq == NULL))
    {
        no_final = no_atual->item;
        return no_final;
    }
    /*Caso nao seja o final da arvore, continua percorrendo os nos*/
    else
    {
        /*Caso o no onde a bola se encontra, tenha sua flag como false, vai 
        para o seu ramo esquerdo e muda a flag para true*/
        if(no_atual->flag == false)
        {
            no_atual->flag = true;
            no_final = percurso_bola(no_atual->esq);
        }
        /*Caso o no onde a bola se encontra, tenha sua flag como true, vai 
        para o seu ramo direito e muda a flag para false*/
        else
        {
            no_atual->flag = false;
            no_final = percurso_bola(no_atual->dir);
        }
        
        return no_final;
    }
}

/*Funcao que desaloca a arvore criada*/
void desaloca(no *no_atual)
{
    /*Caso tenha atingido o no terminal, desaloca-o*/
    if((no_atual->dir == NULL) && (no_atual->esq == NULL))
    {
        free(no_atual);
    }
    /*Caso nao tenha atingido o no terminal, continua percorrendo a arvore*/
    else
    {
        desaloca(no_atual->esq);
        desaloca(no_atual->dir);
        free(no_atual);
    }
}
    



