#include <stdio.h>
#include <stdlib.h>

struct n
{
    int item;
    int flag;
    struct n *esq, *dir;
};
typedef struct n no;

void inicia_arvore(no **raiz);
void cria_arvore(no *no_atual, int posicao, int profundidade);
no *insere_no(int posicao);
void arv_imprime(no *p);

int main()
{
    int profundidade;
    no *raiz = NULL;
    
    scanf("%d", &profundidade);
    
    inicia_arvore(&raiz);
    
    cria_arvore(raiz, 1, profundidade);
    
    arv_imprime(raiz);
    
    return 0;
}

void inicia_arvore(no **raiz)
{
    no *new;
    
    new = malloc(sizeof(no));
    
    new->item = 1;
    new->esq = NULL;
    new->dir = NULL;
    (*raiz) = new;
}

void cria_arvore(no *no_atual, int posicao, int profundidade)
{
    /*Insere o no a esquerda*/
    no_atual->esq = insere_no(posicao *  2);
    
    if(profundidade > 2)
    {
        cria_arvore(no_atual->esq, posicao * 2, profundidade - 1);
    }
    
    /*Insere o no a direita*/
    no_atual->dir = insere_no(((posicao * 2) + 1));
    
    if(profundidade > 2)
    {
        cria_arvore(no_atual->dir, ((posicao * 2) + 1), profundidade - 1);
    }
}

no *insere_no(int posicao)
{
    no *new;
    
    new = malloc(sizeof(no));
    
    new->item = posicao;
    new->esq = NULL;
    new->dir = NULL;
    
    return new;
}

void arv_imprime(no *p) {
    if(p != NULL) {
        arv_imprime(p->esq) ; /* imprime no esquerdo */
        printf("%d\n", p->item) ; /* imprime raiz */
        arv_imprime(p->dir) ; /* imprime no direito */
    }
}