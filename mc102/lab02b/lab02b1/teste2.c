#include <stdio.h>
#include <math.h>

int main(){
    
    int G, C, N, x, i, menornota, e, y, notas, dolar;
    
    printf("Entre com tres valores: ");
    scanf("%d %d %d", &N, &G, &C);
    
    printf("Entre com o valor da base: ");
    scanf("%d", &x);
    
    
    
    for(i = 1, menornota = 0; i <= N; i++){    
        dolar = G * C;
        
        for(e = 0, notas = 0; dolar != 0; notas++){
            
            do{    
        
                y = pow(x, e);
                e++;
        
            }
            while(y < dolar);
            printf("%d\n", dolar);
            if(y != dolar){
                
                dolar = dolar - (int)pow(x, (e - 2));
            
                
            }
            if(y == dolar){
                
                dolar = dolar - (int)pow(x, (e - 1));
            
                
            }
            
            e = 0;
        }
        
        if(notas > menornota){
            
            menornota = notas;
            
        }
        else{
            
            menornota = notas;
            
            
        }  
        scanf("%d", &x);    
    }       
    printf("Valor = %d\n", dolar);
    printf("Notas = %d\n", menornota);    
    
    return 0; 
    
}