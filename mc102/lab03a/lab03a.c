/*Nome: Vitor Kaoru Aoki
  RA: 178474
*/

#include <stdio.h>

int main(){
    
    int n, i, indiv[9], j, x, c, total = 0;
    char v;
    
    scanf("%d %d", &n, &c);
    
    /*Zerando o vetor indiv*/
    for(j = 1; j <= c; j++){
        
        indiv[j] = 0;
        
    }
    
    /*Leitura e armazenamento da quantidade de individuos por casta*/
    for(i = 0; i < n; i++){
        
       for(scanf(" %c", &v); v != '\n'; scanf("%c", &v), total++){
           
           x = v - '0';
           
           indiv[x]++; 
           
        }
       
    }
    
    printf("Total: %d individuos\n", total);
   
    for(j = 1; j <= c; j++){
        
        printf("Total da casta %d: %d\n", j, indiv[j]);
        
    }
    
    /*Calculo e imoressao da porcentagem de individuos por casta*/
    for(j = 1; j <= c; j++){
        
        printf("Percentual da casta %d: %.2f\n", j, ((double)indiv[j] / total) 
* 100);
        
    }
       
    return 0;
       
}