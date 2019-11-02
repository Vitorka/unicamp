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

/*Funcao que monta a arvore, a partir dos percursos in-ordem e pre-ordem. A 
variavel "tamanho", indica o tamanho da sub-arvore atual que esta sendo 
analizada, podendo ela, ser a sub-arvore a esquerda ou a direita, da raiz 
atual. A variavel "raiz_atual", eh utilizada no deslocamento no vetor 
"pre_ordem".*/
no *monta_arvore(char *pre_ordem, char *in_ordem, int tamanho, int inicio, 
                 int raiz_atual, int num_nos)
{
    int i, posicao_raiz, flag = 0, tam_esq = 0, tam_dir = 0;
    no *novo = NULL;  
    
    /*Caso o tamanho seja 0, a sub-arvore representa um no terminal*/
    if(tamanho == 0)
    {
        return NULL;
    }
    else
    {
        novo = insere_no(pre_ordem[raiz_atual]);
        
        /*Continua percorrendo o vetor "pre_ordem", ate que seja atingido o 
        ultimo no da arvore*/
        if(raiz_atual < num_nos - 1)
        {
            /*Procrua o no raiz, no vetor in-ordem, a partir do no selecionado 
            no vetor pre-ordem*/
            for(i = inicio; (flag == 0); i++, tam_esq++)
            {
                if(pre_ordem[raiz_atual] == in_ordem[i])
                {
                    flag = 1;
                    posicao_raiz = i;
                }
            }
            tam_dir = tamanho - tam_esq;
            tam_esq -= 1;
            
            /*Chama recursivamente a funcao, para a sub-arvore a esquerda do no 
            raiz*/
            novo->esq = monta_arvore(pre_ordem, in_ordem, tam_esq, 
                                     posicao_raiz - tam_esq, raiz_atual + 1, 
                                     num_nos);
            
            /*Chama recursivamente a funcao, pra a sub-arvore a direita do no 
            raiz*/
            novo->dir = monta_arvore(pre_ordem, in_ordem, tam_dir, 
                                     posicao_raiz + 1, 
                                     raiz_atual + tam_esq + 1, num_nos);
            
        }
        return novo;
    }
}

/*Funcao que imprime a arvore em pos-ordem*/
void imprime_pos_ordem(no *no_atual)     
{
    if(no_atual != NULL) 
    {
        imprime_pos_ordem(no_atual->esq); 
        imprime_pos_ordem(no_atual->dir); 
        printf("%c", no_atual->item); 
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