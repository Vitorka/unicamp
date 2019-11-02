/* Nome: Vitor Kaoru Aoki
 * RA: 178474
 * Laboratorio 01 - O problema do acesso à lista */

#include <stdio.h>
#include <stdlib.h>

struct l
{
    int item;
    struct l *prox;
};
typedef struct l lista;

lista *inicia_lista(lista *inicio);
lista *cria_lista(lista *ponteiro_aux, int dado);
int MTF(lista *iniMTF, char instrucoes, int dado);
int MTF_acessa(lista *iniMTF, int dado);
int MTF_insere(lista *iniMTF, int dado);
int TR(lista *iniTR, char instrucoes, int dado);
int TR_acessa(lista *iniTR, int dado);
int TR_insere(lista *iniTR, int dado);
int remove_dado(lista *inicio, int dado);
void imprime(lista *inicio, int custo);
void desaloca(lista *inicio);

int main()
{
    int i, tam_ini, requerimentos, dado, custoMTF = 0, custoTR = 0;
    char instrucoes;
    lista *iniMTF = NULL, *auxMTF = NULL, *iniTR = NULL, *auxTR = NULL;
    
    scanf("%d %d", &tam_ini, &requerimentos);
    
    /*Inicia a lista, colocando o no cabeca*/
    iniMTF = inicia_lista(iniMTF);
    auxMTF = iniMTF;
    
    iniTR = inicia_lista(iniTR);
    auxTR = iniTR;
    
    /*Adiciona os dados na lista*/
    for(i = 0; i < tam_ini; i++)
    {
        scanf("%d", &dado);
        auxMTF = cria_lista(auxMTF, dado);
        auxTR = cria_lista(auxTR, dado);
    }
    
    /*Executa as instrucoes passadas*/
    for(i = 0; i < requerimentos; i++)
    {
        scanf(" ");
        scanf("%c", &instrucoes);
        scanf("%d", &dado);
        
        custoMTF += MTF(iniMTF, instrucoes, dado);
        custoTR += TR(iniTR, instrucoes, dado);
    }
    
    /*Imprime as listas modificadas e seus respectivos custos*/
    imprime(iniMTF, custoMTF);
    imprime(iniTR, custoTR);
    
    desaloca(iniMTF);
    desaloca(iniTR);
    
    return 0;
}

/*Funcao que cria uma lista adicionando o no cabeca*/
lista *inicia_lista(lista *inicio)
{
    lista *new;
    
    new = malloc(sizeof(lista));
    
    new->item = -1;
    new->prox = NULL;
    inicio = new;
    
    return inicio;
}

/*Funcao que adiciona os dados na lista*/
lista *cria_lista(lista *ponteiro_aux, int dado)
{
    lista *new;
    
    new = malloc(sizeof(lista));
    
    new->item = dado;
    new->prox = ponteiro_aux->prox;
    ponteiro_aux->prox = new;
    ponteiro_aux = new;
    
    return ponteiro_aux;
}

/*Funcao que executa os comandos de MTF*/
int MTF(lista *iniMTF, char instrucoes, int dado)
{
    int contador = 0;
    
    /*Executa o comando de acesso do MTF*/
    if(instrucoes == 'a') 
    {
        contador = MTF_acessa(iniMTF, dado);
    }
    /*Executa o comando de inserir do MTF*/
    else if(instrucoes == 'i')
    {
        contador = MTF_insere(iniMTF, dado);
    }
    /*Executa o comando de remover do MTF*/
    else if(instrucoes == 'r')
    {
        contador = remove_dado(iniMTF, dado);
    }
    
    return contador;
}

/*Funcao de acesso do MTF*/
int MTF_acessa(lista *iniMTF, int dado)
{
    int contador = 0;
    lista *aux, *aux2;
    
    aux = iniMTF->prox;
    aux2 = iniMTF;
    contador++;
    
    while((aux->item != dado) && (aux != NULL))
    {
        aux = aux->prox;
        aux2 = aux2->prox;
        contador++;
    }
    aux2->prox = aux->prox;
    aux->prox = iniMTF->prox;
    iniMTF->prox = aux;
    
    return contador;
}

/*Funcao de inserir do MTF*/
int MTF_insere(lista *iniMTF, int dado)
{
    int contador = 0;
    lista *aux, *aux2;
    
    aux = iniMTF->prox;
    contador++;
    
    while(aux->prox != NULL)
    {
        aux = aux->prox;
        contador++;
    }
    contador++;
    
    aux2 = malloc(sizeof(lista));
    
    aux2->item = dado;
    aux2->prox = aux->prox;
    aux->prox = aux2;
    
    return contador;
}

/*Funcao que executa os comandos de TR*/
int TR(lista *iniTR, char instrucoes, int dado)
{
    int contador = 0;
    
    /*Executa o comando de acesso do TR*/
    if(instrucoes == 'a')
    {
        contador = TR_acessa(iniTR, dado);
    }
    /*Executa o comando de inserir do TR*/
    else if(instrucoes == 'i')
    {
        contador = TR_insere(iniTR, dado);
    }
    /*Executa o comando de remover do TR*/
    else if(instrucoes == 'r')
    {
        contador = remove_dado(iniTR, dado);
    }
    
    return contador;
}

/*Funcao de acesso do TR*/
int TR_acessa(lista *iniTR, int dado)
{
    int contador = 0, flag = 0;
    lista *aux, *aux2, *aux3;
    
    aux = iniTR->prox;
    aux2 = iniTR;
    aux3 = iniTR;
    contador++;
    
    while((aux->item != dado) && (aux != NULL))
    {
        if(flag == 1)
        {
            aux3 = aux3->prox;
        }
        aux = aux->prox;
        aux2 = aux2->prox;
        
        contador++;
        flag = 1;
    }
    
    if(aux2 != iniTR)
    {
        aux3->prox = aux;
        aux2->prox = aux->prox;
        aux->prox = aux2;
    }
    
    return contador;
}

/*Funcao de inserir do TR*/
int TR_insere(lista *iniTR, int dado)
{
    int contador = 0;
    lista *aux, *aux2, *aux3;
    
    aux = iniTR->prox;
    aux3 = iniTR;
    contador++;
    
    while((aux->prox != NULL) && (aux != NULL))
    {
        aux = aux->prox;
        aux3 = aux3->prox;
        contador++;
    }
    contador++;
    
    aux2 = malloc(sizeof(lista));
    
    aux2->item = dado;
    aux2->prox = aux;
    aux3->prox = aux2;
    
    return contador;
}

/*Funcao que executa o comando de remocao*/
int remove_dado(lista *inicio, int dado)
{
    int contador = 0;
    lista *aux, *aux2;
    
    aux = inicio->prox;
    aux2 = inicio;
    contador++;
    
    while((aux->item != dado) && (aux != NULL))
    {
        aux = aux->prox;
        aux2 = aux2->prox;
        contador++;
    }
    
    aux2->prox = aux->prox;
    free(aux);
    
    return contador;
}

/*Funcao que imprime as listas modificadas e seus respectivos custos*/
void imprime(lista *inicio, int custo)
{
    lista *aux;
    
    printf("%d\n", custo);
    for(aux = inicio; aux != NULL; aux = aux->prox)
    {
        if(aux->prox != NULL)
        {
            printf("%d ", aux->prox->item);
        }
    }
    printf("\n");
}

/*Funcao que desaloca as listas criadas*/
void desaloca(lista *inicio)
{
    lista *aux;
    
    for(aux = inicio; inicio != NULL; aux = inicio)
    {
        inicio = inicio->prox;
        free(aux);
    }
    free(inicio);
}
        
        
    
        