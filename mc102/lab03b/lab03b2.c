/*Nome: Vitor Kaoru Aoki
  RA: 178474
*/

#include <stdio.h>

int main(){
    
    /*Definicao de variaveis, onde a e b, sao, respectivamente, os valores 
minimo e maximo dos intervalos*/
    int a[100], b[100], c[100], d[100], nguard, i, t, m, sinc = 0, pguard = 0;
    
    scanf("%d", &nguard);
    
    for(i = 0;  i < nguard; i++){
        
        a[i] = 0;
        b[i] = 0;
        
    }
    
    for(t = 0; t < nguard; t++){
        
        c[t] = 0;
        d[t] = 0;
        
    }
    
    m = nguard;
    
    /*Leitura dos intervalos*/
    for(i = 0; i < nguard; i++){
        
        scanf("%d", &a[i]);
        scanf("%d", &b[i]);
        
    }
    
    /*Atribuicao da quantidade de guardioes ao vetor de comparacao*/
    for(t = 0; t < nguard; t++, m--){
        
        c[t] = m;
            
    }
    
    /*Verifica se o numero de guardioes pertence ao intervalo*/
    for(t = 0; t < nguard; t++){    
        
        for(i = 0; i < nguard; i++){
            
            if(c[t] >= a[i] && c[t] <= b[i]){
                
                d[t]++;
                
            }
        }   
        
    }
    
    /*Definicao do numero de guardioes sinceros*/
    for(t = 0; t < nguard && sinc == 0; t++){
        
        if(d[t] == c[t]){
            
            sinc = d[t];
            
        }
        
    }
      
    /*Definicao do primeiro guardiao que leva ao cenario mais consistente*/
    for(i = 0; i < nguard && pguard == 0; i++){
        
        if(sinc >= a[i] && sinc <= b[i]){
            
            pguard = ++i;
            
        }
        
    }
    
    printf("Numero de guardioes sinceros = %d\n", sinc);
    printf("Guardiao %d\n", pguard);
    
    return 0;
}