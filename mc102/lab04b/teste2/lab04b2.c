/*Nome: Vitor Kaoru Aoki
  RA: 178474
*/

#include <stdio.h>

int main(){
    
    int dias, capini, vetor[100], i, j, k, l, valor1 = 0, valor2 = 0, valor3 = 
    0, valor4 = 0, valorfin, zinedinezanoni = 0;
    
    scanf("%d %d", &dias, &capini);
    
    for(i = 0; i < dias; i++) {
        
        vetor[i] = 0;
        
    }
    
    for(i = 0; i < dias; i++) {
        
        scanf("%d", &vetor[i]);
        
    }
    
    valorfin = capini;
    
    for(i = 0; i < dias; i++) { 
        
        valor1 = capini / vetor[i];
        printf("valor1 = %d\n", valor1);
        
        for(j = i + 1; j < dias; j++) {
            
            valor2 = (valor1 * vetor[j]) + (capini % vetor[i]);
            printf("valor2 = %d\n", valor2);
            
            for(k = j + 1; k < dias; k++) {
                
                valor3 = valor2 / vetor[k];
                printf("valor3 = %d\n", valor3);
                
                for(l = k + 1; l < dias; l++, zinedinezanoni++) {
                    
                    valor4 = (valor3 * vetor[l]) + (valor2 % vetor[k]);
                    printf("valor4 = %d\n", valor4);
                    
                    if(valor4 > valorfin) {
                        
                        valorfin = valor4;
                        
                    }
                    
                }
                
            }
       
        }
        
    }
    if(valorfin == capini) {
        
        printf("Melhor nao investir agora, cara!\n");
        
    } else {
        
        printf("Capital final = R$%d\n", valorfin);
        
    }
    
    printf("zinedinezanoni = %d\n", zinedinezanoni);
    
    return 0;
}