/*Nome: Vitor Kaoru Aoki
  RA: 178474
*/

#include <stdio.h>

int main(){
    
    int dias, capini, vetor[100], i, j, k, l, valor1 = 0, valor2 = 0, valor3 = 
    0, valor4 = 0, valorfin, dia1, dia2, dia3, dia4;
    
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
       
        for(j = i + 1; j < dias; j++) {
            
            valor2 = (valor1 * vetor[j]) + (capini % vetor[i]);
            
            for(k = j + 1; k < dias; k++) {
                
                valor3 = valor2 / vetor[k];
                
                for(l = k + 1; l < dias; l++) {
                    
                    valor4 = (valor3 * vetor[l]) + (valor2 % vetor[k]);
                    
                    if(valor4 > valorfin) {
                        
                        valorfin = valor4;
                        dia1 = i + 1;
                        dia2 = j + 1;
                        dia3 = k + 1;
                        dia4 = l + 1;
                    }
                    
                }
                
            }
       
        }
        
    }
    if(valorfin == capini) {
        
        printf("Melhor nao investir agora, cara!\n");
        
    } else {
        
        printf("Capital final = R$%d\n", valorfin);
        printf("Compra 1: %d, ", dia1);
        printf("Venda 1: %d\n", dia2);
        printf("Compra 2: %d, ", dia3);
        printf("Venda 2: %d\n", dia4);
        
    }
        
    return 0;
}