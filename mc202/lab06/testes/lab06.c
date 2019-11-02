/* Nome: Vitor Kaoru Aoki
 * RA: 178474
 * Laboratorio 06 - Operações em ABB Auto-ajustáveis */

#include <stdio.h>
#include <stdlib.h>
#include "lab06.h"

/*Funcao que insere um no na arvore*/
no *insere_no(int elemento, no *no_pai)
{
    no *new;
    
    new = malloc(sizeof(no));
    
    new->item = elemento;
    new->esq = NULL;
    new->dir = NULL;
    new->pai = no_pai;
    
    return new;
}

/*Funcao que realiza a rotacao para a direita*/
no *rotacao_dir(no *no_atual)
{
    no *no_pai;
    
    /*Aponta o ponteiro no_pai para o pai do no que sera rotacionado*/
    no_pai = no_atual->pai;
    no_pai->esq = no_atual->dir;
    
    /*Caso o no que sera rotacionado tenha um filho a direita, aponta o campo 
    pai do no-filho para o pai do no retirado*/
    if(no_atual->dir != NULL)
    {
        no_atual->dir->pai = no_pai;
    }
    
    no_atual->dir = no_pai;
    no_atual->pai = no_pai->pai;
    
    /*Verifica se o pai do no retirado, eh filho esquerdo ou direito do avo 
    deste no, para poder liga-lo ao avo*/
    if(no_pai->pai != NULL)
    {
        if(no_pai->item < no_pai->pai->item)
        {
            no_pai->pai->esq = no_atual;
        }
        else 
        {
            no_pai->pai->dir = no_atual;
        }
    }
    
    no_pai->pai = no_atual;

    return no_atual;
}

/*Funcao que realiza a rotacao para a esquerda*/
no *rotacao_esq(no *no_atual)
{
    no *no_pai;
    
    /*Aponta o ponteiro no_pai para o pai do no que sera rotacionado*/
    no_pai = no_atual->pai;
    no_pai->dir = no_atual->esq;
    
    /*Caso o no que sera rotacionado tenha um filho a esquerda, aponta o campo 
    pai do no-filho para o pai do no retirado*/
    if(no_atual->esq != NULL)
    {
        no_atual->esq->pai = no_pai;
    }
    
    no_atual->esq = no_pai;
    no_atual->pai = no_pai->pai;
    
    /*Verifica se o pai do no retirado, eh filho esquerdo ou direito do avo 
    deste no, para poder liga-lo ao avo*/
    if(no_pai->pai != NULL)
    {
        if(no_pai->item < no_pai->pai->item)
        {
            no_pai->pai->esq = no_atual;
        }
        else
        {
            no_pai->pai->dir = no_atual;
        }
    }
    
    no_pai->pai = no_atual;
    
    return no_atual;
}

/*Funcao que realiza o afunilamento da arvore*/
no *afunilamento(no *no_atual)
{ 
    no *no_pai;
    
    no_pai = no_atual->pai;
    
    /*Caso a arvore so tenha um no, nao realiza o afunilamento*/
    if(no_atual->pai == NULL)
    {
        return no_atual;
    }
    
    /*Pai do no_atual eh raiz*/
    if(no_pai->pai == NULL)
    {
        /*Caso o no a ser rotacionado esteja na esquerda de seu pai, realiza a 
        rotacao para a direita*/
        if(no_atual->item < no_pai->item)
        {
            no_atual = rotacao_dir(no_atual);
        }
        /*Caso esteja na direita, realiza a rotacao para a esquerda*/
        else
        {
            no_atual = rotacao_esq(no_atual);
        }
    }
    /*Caso o pai do no_atual nao seja raiz*/
    else
    {   
        /*O no_atual eh filho esquerdo de seu pai*/
        if(no_atual->item < no_pai->item)
        {
            /*Pai do no_atual eh filho esquerdo do avo do no_atual*/
            if(no_pai->item < no_pai->pai->item)
            {
                no_pai = rotacao_dir(no_pai);
                no_atual = rotacao_dir(no_atual);
            }
            /*Pai do no_atual eh filho direito do avo do no_atual*/
            else 
            {
                no_atual = rotacao_dir(no_atual);
                no_atual = rotacao_esq(no_atual);
            }
        }
        /*O no_atual eh filho direito de seu pai*/
        else
        {
            /*Pai do no_atual eh filho direito do avo do no_atual*/
            if(no_pai->item > no_pai->pai->item)
            {
                no_pai = rotacao_esq(no_pai);
                no_atual = rotacao_esq(no_atual);
            }
            /*Pai do no_atual eh filho esquerdo do avo do no_atual*/
            else 
            {
                no_atual = rotacao_esq(no_atual);
                no_atual = rotacao_dir(no_atual);
            }
        }
    }
    
    /*Caso o no_atual seja a raiz, retorna*/
    if(no_atual->pai == NULL)
    {
        return no_atual;
    }
    /*Caso contrario, continua o afunilamento*/
    else
    {
        return afunilamento(no_atual);
    }
}

/*Funcao que insere um elemento na arvore*/
no *insere(int elemento, no *no_atual)
{
    /*Caso o elemento a ser inserido, seja menor que o no_atual, vai para a 
    esquerda*/
    if(elemento < no_atual->item)
    {
        /*Se nao existir nenhum no a esquerda do no_atual, insere o elemento e 
        realiza a rotacao*/
        if(no_atual->esq == NULL)
        {
            no_atual->esq = insere_no(elemento, no_atual);
            return afunilamento(no_atual->esq);
        }
        
        /*Caso contrario, continua percorrendo a arvore*/
        return insere(elemento, no_atual->esq);
    }
    /*Caso o elemento a ser inserido, seja maior que o no_atual, vai para a 
    direita*/
    else if(elemento > no_atual->item)
    {
        /*Se nao existir nenhum no a direita do no_atual, insere o elemento e 
        realiza a rotacao*/ 
        if(no_atual->dir == NULL)
        {
            no_atual->dir = insere_no(elemento, no_atual);
            return afunilamento(no_atual->dir);
        }
        
        /*Caso contrario, continua percorrendo a arvore*/
        return insere(elemento, no_atual->dir);
    }
    
    /*Caso o elemento nao exista na arvore, realiza o afunilamento com o ultimo 
    no acessado*/
    return afunilamento(no_atual);
}

/*Funcao que busca um elemento na arvore*/
no *busca(int elemento, no *no_atual)
{
    /*Caso o elemento seja menor do que o no_atual, e exista filho a esquerda, 
    vai para a esquerda*/ 
    if((elemento < no_atual->item) && (no_atual->esq != NULL))
    {
        return busca(elemento, no_atual->esq);  
    }
    /*Caso o elemento seja maior do que o no_atual, e exista filho a direita, 
    vai para a direita*/
    else if((elemento > no_atual->item) && (no_atual->dir != NULL))
    {
        return busca(elemento, no_atual->dir);
    }
    
    /*Caso o elemento tenha sido encontrado, realiza o afunilamento com o no 
    que contem o elemento. Caso ele nao exista, realiza o afunilamento com o 
    ultimo no acessado*/
    return afunilamento(no_atual);   
}

/*Funcao que realiza a busca do no que ira substituir o no que foi retirado*/
no *remove_busca(no *no_atual)
{   
    if(no_atual->dir != NULL)
    {
        return remove_busca(no_atual->dir);
    }
    
    return no_atual;
}

/*Funcao que remove um elemento da arvore*/
no *remove_no(int elemento, no *no_atual)
{   
    no *no_auxiliar, *no_auxiliar2;
    
    /*Caso tenha encontrado o elemento na arvore, retira-o*/
    if(elemento == no_atual->item)
    {
        /*Caso o no a ser retirado possuir dois filhos*/
        if((no_atual->esq != NULL) && (no_atual->dir != NULL))
        {
            no_auxiliar = remove_busca(no_atual->esq);
            no_auxiliar2 = no_auxiliar->pai;
            
            /*Verifica se o no que ira trocar, eh filho direto do no retirado*/
            if(no_atual == no_auxiliar2)
            {
                /*Caso o no que ira substituir o no que sera retirado, possuir 
                filho, liga-o ao avo*/
                if(no_auxiliar->esq != NULL)
                {
                    no_auxiliar2->esq = no_auxiliar->esq;
                    no_auxiliar->esq->pai = no_auxiliar2;
                }
                /*Caso nao possua filho, faz o avo apontar para NULL*/ 
                else
                {
                    no_auxiliar2->esq = NULL;
                }
                
                no_atual->item = no_auxiliar->item;
                free(no_auxiliar);
            }
            /*Caso o no que ira trocar, nao eh filho direto do no retirado*/
            else
            {
                /*Caso o no que ira substituir o no que sera retirado, possuir 
                filho, liga-o ao avo*/
                if(no_auxiliar->esq != NULL)
                {
                    no_auxiliar2->dir = no_auxiliar->esq;
                    no_auxiliar->esq->pai = no_auxiliar2;
                }
                /*Caso nao possua filho, faz o avo apontar para NULL*/ 
                else
                {
                    no_auxiliar2->dir = NULL;   
                }
                
                no_atual->item = no_auxiliar->item;
                free(no_auxiliar);
            }
            
            return afunilamento(no_auxiliar2);
        }
        /*Caso o no a ser retirado possuir um filho*/
        else
        {
            no_auxiliar = no_atual->pai;
            
            /*Caso ele possua um filho a esquerda*/
            if(no_atual->esq != NULL)
            {
                no_atual->esq->pai = no_auxiliar;
                
                /*Se o no a ser retirado nao for raiz*/
                if(no_auxiliar != NULL)
                {
                    if(no_atual->item < no_auxiliar->item)
                    {
                        no_auxiliar->esq = no_atual->esq;
                    }
                    else
                    {
                        no_auxiliar->dir = no_atual->esq;
                    }
                    
                    free(no_atual);
                    
                    return afunilamento(no_auxiliar);
                }
                
                /*Caso o no a ser retirado seja raiz*/
                no_auxiliar2 = no_atual->esq;
                free(no_atual);
                    
                return no_auxiliar2;
            }
            /*Caso ele possua um filho a direita*/
            else if(no_atual->dir != NULL)
            {
                no_atual->dir->pai = no_auxiliar;
                
                /*Se o no a ser retirado nao for raiz*/
                if(no_auxiliar != NULL)
                {
                    if(no_atual->item < no_auxiliar->item)
                    {
                        no_auxiliar->esq = no_atual->dir;
                    }
                    else
                    {
                        no_auxiliar->dir = no_atual->dir;
                    }
                    
                    free(no_atual);
                   
                    return afunilamento(no_auxiliar);
                }
                
                /*Caso o no a ser retirado seja raiz*/
                no_auxiliar2 = no_atual->dir;
                free(no_atual);
                
                return no_auxiliar2;
            }
            /*Caso o no a ser retirado nao possuir nenhum filho*/
            else
            { 
                /*Se o no a ser retirado nao for raiz*/
                if(no_auxiliar != NULL)
                {
                    if(no_atual->item < no_auxiliar->item)
                    {
                        no_auxiliar->esq = NULL;
                    }
                    else
                    {
                        no_auxiliar->dir = NULL;
                    }
                    
                    free(no_atual);
                    
                    return afunilamento(no_auxiliar);
                }
                
                /*Caso o no a ser retirado for raiz*/
                free(no_atual);
                
                return no_auxiliar;
            }
        }
    }
    /*Caso nao tenha encontrado o elemento, continua percorrendo a arvore, ou, 
    caso o no nao seja encontrado utiliza o ultimo no acessado no afunilamento*/
    else
    {
        /*Se o elemento for menor do que o no_atual, vai para a esquerda*/
        if((elemento < no_atual->item) && (no_atual->esq != NULL))
        {
            return remove_no(elemento, no_atual->esq);
        }
        /*Se o elemento for maior que  o no_atual, vai para a direita*/
        else if((elemento > no_atual->item) && (no_atual->dir != NULL))
        {
            return remove_no(elemento, no_atual->dir);         
        }
        
        return afunilamento(no_atual);
    }
}
    
/*Funcao que cria a arvore a partir da entrada dada*/
no *cria_arvore(int num_elem, no *raiz)
{
    int i, elemento;
    
    for(i = 1; i < num_elem; i++)
    {
        scanf("%d", &elemento);
        raiz = insere(elemento, raiz);
    }
    
    return raiz;
}

/*Funcao que realiza as operacoes dadas*/
no *realiza_operacoes(no *raiz)
{
    char operacao;
    int elemento;
    
    scanf(" ");
    scanf("%c", &operacao);
    
    while(operacao != 'f')
    {
        switch(operacao)
        {
            /*Caso a operacao dada for 'i', realiza a insercao e o 
            afunilamento*/
            case 'i':
                scanf("%d", &elemento);
                raiz = insere(elemento, raiz);
                break;
            
            /*Caso a operacao dada for 'b', realiza a busca e o afunilamento*/
            case 'b':
                scanf("%d", &elemento);
                raiz = busca(elemento, raiz);
                break;
        
            /*Caso a operacao dada for 'r', realiza a remocao e o afunilamento*/
            case 'r':
                scanf("%d", &elemento);
                raiz = remove_no(elemento, raiz);
                break;
        }
        scanf(" ");
        scanf("%c", &operacao);
    }
    
    return raiz;
}

/*Funcao que imprime os nos da arvore em in-ordem*/
void inordem(no *no_atual)     
{
    if(no_atual != NULL) 
    {
        inordem(no_atual->esq); 
        printf(" %3d", no_atual->item);
        inordem(no_atual->dir); 
    }
}

/*Funcao que imprime os nos da arvore em pre-ordem*/
void pre_ordem(no *no_atual)     
{
    if(no_atual != NULL) 
    {
        printf(" %3d", no_atual->item);
        pre_ordem(no_atual->esq); 
        pre_ordem(no_atual->dir); 
    }
}

/*Funcao que desaloca a arvore criada*/
void desaloca(no *no_atual)
{
    if(no_atual != NULL)
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
}