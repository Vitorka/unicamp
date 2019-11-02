/* Nome: Seu nome aqui
 * RA: Seu RA aqui
 * Laboratorio 03 - Sistema Único de Saúde */

#include <stdio.h>
#include <stdlib.h>

struct f
{
    int item;
    struct f *prox;
};
typedef struct f fila;

fila *inicia_fila(fila *inicio);
fila *cria_fila(fila *fim_fila, int dado);
void emergencia(fila *inicio, fila *aux, fila *aux2, fila **fim_fila);
void atendimento(fila *inicio, fila *aux, fila **fim_fila);
void SUS(fila *inicio, fila **fim_fila, char categorias);
void desaloca(fila *inicio);

int main()
{
    int i, pacientes;
    char categorias;
    fila *inicio = NULL, *fim_fila = NULL;
    
    scanf("%d", &pacientes);
    
    inicio = inicia_fila(inicio);
    fim_fila = inicio;
    
    for(i = 0; i < pacientes; i++)
    {
        fim_fila = cria_fila(fim_fila, (i + 1));
    }
    
    scanf(" ");
    scanf("%c", &categorias);
    
    while(categorias != 'F')
    {
        SUS(inicio, &fim_fila, categorias);
        
        scanf(" ");
        scanf("%c", &categorias);
    }
    
    desaloca(inicio);
    return 0;   
}

/*Funcao que cria uma fila adicionando o no cabeca*/
fila *inicia_fila(fila *inicio)
{
    fila *new;
    
    new = malloc(sizeof(fila));
    
    new->item = -1;
    new->prox = NULL;
    inicio = new;
    
    return inicio;
}

/*Funcao que adiciona os dados na fila*/
fila *cria_fila(fila *fim_fila, int dado)
{
    fila *new;
    
    new = malloc(sizeof(fila));
    
    new->item = dado;
    new->prox = fim_fila->prox;
    fim_fila->prox = new;
    fim_fila = new;
    
    return fim_fila;
}

/*Funcao que coloca o paciente classificado em emergencia no inicio da fila de 
atendimento*/
void emergencia(fila *inicio, fila *aux, fila *aux2, fila **fim_fila)
{
    /*Verifica se o paciente em emergencia nao eh o ultimo da fila. Caso for, 
    muda o ponteiro de final da fila, para o penultimo paciente*/
    if(*fim_fila == aux)
    {
        *fim_fila = aux2;
    }
    aux2->prox = aux->prox;
    aux->prox = inicio->prox;
    inicio->prox = aux;
}

/*Funcao que executa o atendimento dos pacientes, colocando o paciente atendido 
no final da fila*/
void atendimento(fila *inicio, fila *aux, fila **fim_fila)
{
    inicio->prox = aux->prox;
    aux->prox = (*fim_fila)->prox;
    (*fim_fila)->prox = aux;
    (*fim_fila) = aux;
}

/*Funcao que verifica se a categoria que sera executada eh um atendimento 
normal, ou uma emergencia*/
void SUS(fila *inicio, fila **fim_fila, char categorias)
{
    int paciente, flag = 0;
    fila *aux, *aux2;
    
    /*Executa o comando caso seja um atendimento normal*/
    if(categorias == 'A')
    {
        printf("%d\n", inicio->prox->item);
        atendimento(inicio, inicio->prox, fim_fila);
    }
    /*Executa o comando caso seja uma emergencia*/
    else if(categorias == 'E')
    {
        scanf("%d", &paciente);
        
        /*Procura o paciente em estado de emergencia. Flag = 1, indica que ele 
        foi encontrado e a busca pode parar*/
        for(aux = inicio->prox, aux2 = inicio; (aux != NULL) && (flag == 0); 
            aux = aux->prox, aux2 = aux2->prox)
        {
            if(aux->item == paciente)
            {
                emergencia(inicio, aux, aux2, fim_fila);
                flag = 1;
            }
        }
    }
}

/*Funcao que desaloca a fila criada*/
void desaloca(fila *inicio)
{
    fila *aux;
    
    for(aux = inicio; inicio != NULL; aux = inicio)
    {
        inicio = inicio->prox;
        free(aux);
    }
    free(inicio);
}