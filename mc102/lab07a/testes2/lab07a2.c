/*Nome: Vitor Kaoru Aoki
RA: 178474
*/

#include <stdio.h>
int main(){int i, j, k, l, m, n, posicoes, max_caixas, 
num_exec, num_prog, num_comand, condicao, acidente = 0; char caixas[10][10], 
execucoes[60], comando[9][60], braco = '0'; scanf("%d %d %d %d %d", &posicoes, 
&max_caixas, &num_prog, &num_comand, &num_exec); scanf(" "); for(i = 0; i < 
max_caixas; i++) {scanf("%s", caixas[i]);} scanf(" "); scanf("%s", execucoes); 
scanf(" "); for(j = 1; j <= num_prog; j++) {scanf("%s", comando[j]);} for(k = 
0, n = 0; (k < num_exec) && (acidente == 0); k++) {l = execucoes[k] - '0'; 
for(m = 0; (comando[l][m] != '*') && (acidente == 0); m++, i = 0) {condicao = 
0; if((comando[l][m] == 'B') && (braco == 'B')) {condicao = 1; m++;} else 
if((comando[l][m] == 'G') && (braco == 'G')) {condicao = 1; m++;} else 
if((comando[l][m] == 'Y') && (braco == 'Y')) {condicao = 1; m++;} else 
if((comando[l][m] == 'A') && (braco != '0')) {condicao = 1; m++;} else 
if((comando[l][m] == 'N') && (braco == '0')) {condicao = 1; m++;} else 
if((comando[l][m] == 'L') || (comando[l][m] == 'R') || (comando[l][m] == 'D')) 
{condicao = 1;} if(condicao == 1) {if((comando[l][m] == 'L') && (n != 0)) 
{if((caixas[0][n - 1] != '.') && (braco != '0')) {acidente = 1;} else 
{n--;}} else if((comando[l][m] == 'R') && (n != posicoes - 1)) {if((caixas[0][n 
+ 1] != '.') && (braco != '0')) {acidente = 1;} else {n++;}} else 
if(comando[l][m] == 'D') {if(braco == '0') {for(i = 0; (i < max_caixas) && 
(braco == '0'); i++) {if(caixas[i][n] != '.') {braco = caixas[i][n]; 
caixas[i][n] = '.';}}} else {for(i = 0; (i < max_caixas) && (braco != '0'); 
i++){if(caixas[i][n] != '.') {caixas[i - 1][n] = braco; braco = '0';} else if(i 
== max_caixas - 1) {caixas[i][n] = braco; braco = '0';}}}}} else 
{m++;}}} if(acidente == 1) {printf("Um acidente ocorreu\n");} else {for(i = 0; 
i < max_caixas; i++, printf("\n")) {printf("%s", caixas[i]);} } return 0;}

