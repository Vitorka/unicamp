/*Nome: Vitor Kaoru Aoki
  RA: 178474
*/

#include <stdio.h>

int main() {
    
    /*Declaracao de variaveis, onde x representa o numero de posicoes 
    existentes e y representa o numero maximo de caixas que podem ser 
    empilhadas*/
    int posicoes[10], i, x, y, segcaixa, acidente = 0;
    char comandos;
    
    scanf("%d %d", &x, &y);
    
    for(i = 0; i < x; i++) {
        posicoes[i] = 0;    
    }
    
    for(i = 0; i < x; i++) {
        scanf("%d", &posicoes[i]);
    }
    
    for(scanf(" %c", &comandos), i = 0, segcaixa = 0; (comandos != '*') && 
    (acidente != 1); scanf("%c", &comandos)) {
        
        /*Executa os comandos para o movimento do braco para a direita*/
        if(comandos == 'R') {
            if(i < x - 1) {
                i++;
            }
            
            /*Reconhece quando o movimento do braco causa um acidente*/
            if((segcaixa == 1) && (posicoes[i] == y)) {
                   acidente = 1;
            }
        }
        
        /*Executa os comandos para o movimento do braco para a esquerda*/
        if(comandos == 'L') {
            if(i > 0){
                i--;
            }  
            
            /*Reconhece quando o movimento do braco causa um acidente*/
            if((segcaixa == 1) && (posicoes[i] == y)) {
                acidente = 1;    
            }
        }
        
        /*Executa os comandos para a descida do braco*/
        if(comandos == 'D') {
            
            /*Se o braco nao segura nenhuma caixa, pega a caixa da pilha na 
            qual se encontra. Caso contrario, se estiver segurando alguma 
            caixa, deposita-a na pilha na qual se encontra*/
            if(segcaixa == 0) {
                if(posicoes[i] != 0) {
                    posicoes[i]--;
                    segcaixa++;
                }
            } else {
                if(posicoes[i] < y) {
                    posicoes[i]++;
                    segcaixa--;
                }
            }  
        }
    }
    
    if(acidente == 1) {
        printf("Um acidente ocorreu\n");
    } else {
        for(i = 0; i < x - 1; i++) {
            printf("%d ", posicoes[i]);
        }
        printf("%d\n", posicoes[i]);
    }
    return 0;
}