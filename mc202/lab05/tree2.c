#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

/*Funcao que le e armazena os percursos in-ordem e pre-ordem*/
void le_percurso(char *percurso, int num_nos)
{
    int i;
    
    scanf(" ");
    for(i = 0; i < num_nos; i++)
    {
        scanf("%c", &percurso[i]);
    }
}

/*Funcao que insere um no a arvore*/
no *insere_no(char caractere)
{
    no *new;
    
    new = malloc(sizeof(no));
    
    new->item = caractere;
    new->esq = NULL;
    new->dir = NULL;
    
    return new;
}

/*Funcao que monta a arvore, a partir dos percursos in-ordem e pre-ordem*/
no *monta_arvore(char *pre_ordem, char *in_ordem, int raiz_atual, int num_nos)
{
    int i, posicao_raiz, flag = 0, tam_esq = 0, tam_dir = 0;
    no *novo = NULL;
    
    /*Procrua o no raiz, no vetor in-ordem, a partir do no selecionado no vetor 
    pre-ordem*/
    for(i = inicio; (flag == 0) && (i < num_nos); i++, tam_esq++)
    {
        if(pre_ordem[raiz_atual] == in_ordem[i])
        {
            flag = 1;
            posicao_raiz = i;
        }
    }
    
    tam_dir = tamanho - tam_esq;
    tam_esq -= 1;
    
    if(tamanho == 0)
    {
        return NULL;
    }
    else
    {
        novo = insere_no(pre_ordem[raiz_atual]);
        
        if(raiz_atual < num_nos - 1)
        {
            /*Esquerda*/
            novo->esq = monta_arvore(pre_ordem, in_ordem, tam_esq, 
                                     posicao_raiz - tam_esq, raiz_atual + 1, 
                                     num_nos);
            
            /*Direita*/
            novo->dir = monta_arvore(pre_ordem, in_ordem, tam_dir, 
                                     posicao_raiz + 1, raiz_atual + 
                                     tam_esq + 1, num_nos);
            
        }
        return novo;
    }
}

void imprime_pos_ordem(no *raiz)     
{
    if(raiz != NULL) 
    {
        imprime_pos_ordem(raiz->esq); 
        imprime_pos_ordem(raiz->dir); 
        printf("%c", raiz->item); 
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
        if(no_atual->esq != NULL)
        {
            desaloca(no_atual->esq);
        }
        
        if(no_atual->dir != NULL)
        {
            desaloca(no_atual->dir);
        }
        
        free(no_atual);
    }
}