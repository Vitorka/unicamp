/*Nome: Vitor Kaoru Aoki
 * RA: 178474
 */

#include <stdio.h>

/*O programa, a partir dos dados de densidade de pessoas por quadra, calcula a 
quadra onde o Raio Sugestor deve ser colocado para que sua area de alcance 
atinja o maior numero possivel de pessoas, e ao final, mostra qual e o maior 
numero possivel de pessoas atingidas por ele*/
int main(){
    
    int densidade[50][50], lin, col, alcance, i, j, k, l, m, n, area, 
    tam_lin, tam_col, soma, quant_max = 0;
    
    scanf("%d %d %d", &lin, &col, &alcance);
    
    for(i = 0; i < lin; i++) {
        
        for(j= 0; j < col; j++) {    
            scanf("%d", &densidade[i][j]);
        }
    }
    
    /*Define o tamanho da area de alcance, a partir do valor de alcance dado e 
    determina os valores maximos de alcance para linhas e colunas da matriz 
    densidade*/
    area = (alcance * 2) + 1;
    tam_lin = area;
    tam_col = area;
    
    /*Faz a soma da densidade de todas as areas possiveis cobertas pelo Raio 
    Sugestor e identifica qual a que possui o maior numero de pessoas afetadas 
    pelo raio*/
    for(k = 0; k < (lin - area + 1); k++, tam_lin++, tam_col = area) {
        
        for(l = 0, soma = 0; l < (col - area + 1); l++, tam_col++, soma = 0) {
            
            for(m = k; m < tam_lin; m++) {
               
               for(n = l; n < tam_col; n++) {
               
                   soma += densidade[m][n];
                   
                   if(soma > quant_max) {
                       quant_max = soma;
                   }
               }
           }
        }
    }
    
    printf("%d\n", quant_max);

    return 0;
}