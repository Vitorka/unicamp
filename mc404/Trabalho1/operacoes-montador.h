#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#ifndef OPERACOES_MONTADOR_H_INCLUDED_
#define OPERACOES_MONTADOR_H_INCLUDED_

typedef struct rot {
    char nome_rotulo[65]; //Armazena o nome do rotulo
    char endereco[4]; //Armazena o endereco ao qual o rotulo se refere
    int rotulo_existente; //Variavel que identifica se o rotulo ja foi declarado
    int pos_mont; //Variavel que indica se o rotulo se refere a uma posicao de montagem a esquerda ou a direita
    long int end_mapa; //Variavel que armazena a posicao do mapa de memoria a qual o rotulo esta relacionado
    struct rot *prox;
}rotulos;

typedef struct direct {
    char simbolo[65]; //Armazena o simbolo a qual o .set se refere
    char valor[11]; //Armazena o valor a qual se refere esse simbolo
    int set_existente; //Variavel que indica se o .set ja foi declarado
    struct direct *prox;
}sets;

typedef struct map {
    char palavra[11]; //Armazena a palavra do mapa de memoria
    char rotulo_esq[65]; /*Armazena o rotulo correspondente ao lado esquerdo da palavra de memoria, caso ele precise 
                         ser completado posteriormente*/
    char rotulo_dir[65]; /*Armazena o rotulo correspondente ao lado direito da palavra de memoria, caso ele precise ser 
                         completado posteriormente*/
    char set[65]; //Armazena o .set correspondente a palavra de memoria, caso ela precise ser completada posteriormente
    int num_linha; /*Armazena o numero da linha do arquivo de entrada correspondente as informacoes da respectiva linha 
                   do mapa de memoria*/
} mapa;

rotulos *insere_rotulos(char *rotulo, rotulos *raiz, long int pos_mont, int dir_esq, int rotulo_existente);
sets *insere_sets(char *argumento1, char *argumento2, sets *inicio, int set_existente);
void adiciona_palavras(char *palavra, mapa *mapa_memoria, long int linha);
void imprime_lista_rotulos(rotulos *rot);
int adiciona_instrucao(char *opcode, char *endereco, mapa *mapa_memoria, long int linha, int dir_esq);
void imprime_lista_sets(sets *set);
void completa_mapa(rotulos *inicio_rotulos, sets *inicio_sets, mapa *mapa_memoria, int argc, FILE *arqs, FILE *arqe);
void desaloca_rotulos(rotulos *rot);
void desaloca_sets(sets *set);

#endif
