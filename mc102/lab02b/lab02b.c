/*Nome: Vitor Kaoru Aoki
  RA: 178474
*/

#include <stdio.h>
#include <math.h>

int main(){
    
    int G, C, N, notas, i, menornota, e, y, Nnotas, delficos;
    
    scanf("%d %d %d", &N, &G, &C);
         
    for(i = 1, menornota = 0; i <= N; i++){    
        
        scanf("%d", &notas);
        
        /*Calculo do valor de dolares elficos totais*/
        delficos = G * C;
        
        for(e = 0, Nnotas = 0; delficos != 0; Nnotas++){
            
            /*Calculo da quantidade de notas minimas*/
            do{    
                
                y = pow(notas, e);
                e++;
                
            }
            while(y < delficos);
            
            if(y != delficos){
                
                delficos = delficos - (int)pow(notas, (e - 2));
                
                
            }
            if(y == delficos){
                
                delficos = delficos - (int)pow(notas, (e - 1));
                
            }
            
            e = 0;
        }
        
        /*Comparacao para a obtencao da menor quantidade de notas*/
        if(i == 1){
            
            menornota = Nnotas;
        }
        else if(Nnotas < menornota){
            
            menornota = Nnotas;
            
        }
        
    }       
    
    printf("Numero minimo de notas = %d\n", menornota);    
    
    return 0; 
    
}