#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#ifndef CONVERSOES_H_INCLUDED_
#define CONVERSOES_H_INCLUDED_


char *retorna_instrucao(char *instrucao);
char *dec_para_hexa(long int decimal);
long int dec_para_dec(char *decimal);
long int hexa_para_decimal(char *hexa);
long int transforma_dec_para_dec(char *decimal);
long int potencia(int pow, int tipo);

#endif
