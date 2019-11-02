/* Nome: Vitor Kaoru Aoki 
 * RA: 178474 
 * Laboratorio 07 - Filas de Prioridade com Duas Extremidades */

#include <stdio.h>
#include <stdlib.h>
#define MAX 258

typedef struct h
{
    int minimo;
    int maximo;
} Heap;

/*Funcao que zera o vetor de structs*/
void zera_vetor(Heap heap[MAX]);

/*Funcao que verifica se os intervalos de minimo e maximo estao corretos*/
void verifica_maximo_minimo(int posicao, Heap heap[MAX]);

/*Funcao que organiza o heap de entrada, corrigindo os intervalos*/
void arruma_heap(int num_elem, Heap heap[MAX]);

/*Funcao que cria o heap inicial*/
void cria_heap(int num_elem, Heap heap[MAX]);

/*Funcao que realiza as operacoes dadas*/
void operacoes(int *num_elem, Heap heap[MAX]);

/*Funcao que realiza a descida no heap de minimo*/
void desce_heap_minimo(int num_elem, int posicao, Heap heap[MAX]);

/*Funcao que realiza a descida no heap de maximo*/
void desce_heap_maximo(int num_elem, int posicao, Heap heap[MAX]);

/*Funcao que realiza a subida no heap*/
void sobe_heap(int num_elem, int posicao, Heap heap[MAX]);

/*Funcao que insere um elemento no heap*/
void insere(int *num_elem, int elemento, Heap heap[MAX]);

/*Funcao que remove um elemento do heap*/
void remocao(int *num_elem, char operacao, Heap heap[MAX]);

/*Funcao que imprime o heap minimo em pre-ordem*/
void imprime_preordem_min(int num_elem, int posicao, Heap heap[MAX]);

/*Funcao que imprime o heap maximo em pre-ordem*/
void imprime_preordem_max(int num_elem, int posicao, Heap heap[MAX]);

/*Funcao que imprime os heaps*/
void imprime(int num_elem, Heap heap[MAX]);

