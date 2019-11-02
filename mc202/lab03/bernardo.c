/* Nome: Bernardo Lanza de Assunção
 * RA: 164836
 * Laboratorio 03 - Sistema Único de Saúde */
 
 
/* Implementacao do TAD */

#include<stdio.h>
#include<stdlib.h>

typedef struct lista_encadeada{
    int info;
    struct lista_encadeada *prox;
} fila;

fila *fila_cria(void);
void fila_insere(fila **head, int number);
void fila_libera(fila *Fila);


int main(){
    int size, pacient, i;
    char command;
    fila *SUS = fila_cria();
    fila *aux1;
    fila *aux2;
    
    scanf("%d", &size);
    
    for(i=2;i<=size;i++){
        fila_insere(&SUS, i);   
    }
    
    SUS = SUS->prox;
    
    scanf("%c", &command);
    while(command != 'F'){
    
        switch(command){
        
            case 'A':
                printf("%d\n", SUS->info);
                SUS = SUS->prox;
                break;
                
            case 'E':
                aux1 = SUS;
                scanf("%d", &pacient);
                while( (aux1->prox)->info != pacient ){
                    aux1 = aux1->prox;
                }
                aux2 = aux1->prox;
                aux1->prox = aux2->prox;
                (aux1->prox)->prox = aux2;
                aux2->prox = SUS;
                SUS = aux2;
                
                break;
        }
        
        scanf("%c", &command);
    } 
    return 0;
}

fila *fila_cria(void){
    fila *novaFila = (fila *)malloc(sizeof(fila));
    novaFila->prox = novaFila;
    novaFila->info = 1;
    return novaFila;
}

void fila_insere(fila **head, int number){
    fila *auxFila;
    auxFila = (fila *)malloc(sizeof(fila));
    auxFila->info = number;
    auxFila->prox = (*head)->prox;
    (*head)->prox = auxFila;
    *head = auxFila;
}

void fila_libera(fila *Fila){
    fila *auxFila1;
    fila *auxFila2;
    
    auxFila1 = Fila->prox;
    while(auxFila1 != Fila){
        auxFila2 = auxFila1->prox;
        free(auxFila1);
        auxFila1 = auxFila2;
    }
    
    free(Fila);
}