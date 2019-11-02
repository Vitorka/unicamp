#include <stdio.h>
int main() {
char palavra1[21], palavra2[21];
int i, anagramas = 1, caracteres[128];
printf("Entre com duas palavras: ");
scanf("%s %s", palavra1, palavra2);
/* inicializa o vetor de frequencia de caracteres */
for (i = 0; i < 128; i++)
caracteres[i] = 0;
/* conta os caracteres encontrados na palavra1 */
for (i = 0; palavra1[i]; i++)
caracteres[(int) palavra1[i]]++;
/* conta os caracteres encontrados na palavra2 */
for (i = 0; palavra2[i]; i++)
caracteres[(int) palavra2[i]]--;
/* verifica se as palavras tem a mesma frequencia de caracteres */
for (i = 0; i < 128; i++)
if (caracteres[i] != 0)
anagramas = 0;
if (anagramas)
printf("As duas palavras sao anagramas\n");
else
printf("As duas palavras nao sao anagramas\n");
return 0;
}