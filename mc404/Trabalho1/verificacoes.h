#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "conversoes.h"
#include "operacoes-montador.h"
#include "impressoes.h"
#ifndef VERIFICACOES_H_INCLUDED_
#define VERIFICACOES_H_INCLUDED_

int hexa_valido(char *endereco);
int dec_valido(char *endereco);
int palavra_valida(char *endereco);
int verifica_rotulo(char *rotulo);
int verifica_rotulo(char *rotulo);
int verifica_comentario(char *comentario);
int verifica_diretiva(char *diretiva);
int verifica_sintaxe_linha(char *palavra, int id, int num_linha, int argc, FILE *arqs, FILE *arqe, 
                           mapa *mapa_memoria, rotulos *inicio_rotulos, sets *inicio_sets);
rotulos *verifica_rotulo_existente(rotulos *inicio_rotulos, char *palavra);
sets *verifica_set_existente(sets *inicio_sets, char *palavra);

#endif
