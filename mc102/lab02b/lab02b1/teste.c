#include <stdio.h>
#include <math.h>

int main(){
    
    int x, b = 0, y, G, C, N, notas = 0, i, z = 0;
    
    printf("Entre com tres valores: ");
    scanf("%d %d %d",&N, &G, &C);
    
    printf("Entre com os valores de base: ");
    scanf("%d", &x);
    
    for(i = 1; i <= N; i ++, scanf("%d", &x)){
        
        while(y != 0){
                       
            while(y < (G * C)){
            
                y = pow(x, b);
                b ++;
                
            }
                
        notas++;
        y = (G * C) - (pow(x, (b - 2)));
              
        }
        
        if(notas > z){
        
            z = notas;
            
        }
        else{
            
            z = notas;
        
            
        }
        
    }
    
    printf("Total = %d\n", y);
    printf("Notas = %d\n", z);
    
    return 0;
}
    
    