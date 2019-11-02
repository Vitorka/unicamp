#include <stdio.h>
#include "operacoes-montador.h"
#include "conversoes.h"
#ifndef IMPRESSOES_H_INCLUDED_
#define IMPRESSOES_H_INCLUDED_

void imprime_mapa(mapa *mapa_memoria, int argc, FILE *arqs);
void imprime_erros(int num_linha, char *mensagem_erro, char *argumento, int argc, FILE *arqs, FILE *arqe, 
                   mapa *mapa_memoria, rotulos *inicio_rotulos, sets *inicio_sets);

#endif
