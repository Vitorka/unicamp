/*Nome: Vitor Kaoru Aoki
  RA: 178474
*/

#include <stdio.h>

/*Programa que define qual guardiao e o sincero, a partir da comparacao entre 
o que e dito por cada guardiao*/
int main(){
    
    /*Definicao de variaveis, onde os vetores a e b, sao, respectivamente, os 
    valores minimo e maximo dos intervalos, e os vetores, c, d e e sao vetores 
    auxiliares*/
    int a[100], b[100], c[100], d[100], e[100], nguard, i, t, m, sinc = 0, 
    pguard = 0;
    
    scanf("%d", &nguard);
    
    for(i = 0;  i < nguard; i++){
        
        a[i] = 0;
        b[i] = 0;
        
    }
    
    for(t = 0; t < nguard; t++){
        
        c[t] = 0;
        d[t] = 0;
        e[t] = 0;
        
    }
    
    m = nguard;
    
    /*Leitura dos intervalos*/
    for(i = 0; i < nguard; i++){
        
        scanf("%d", &a[i]);
        scanf("%d", &b[i]);
        
    }
    
    /*Atribuicao de todas as quantidades possiveis de guardioes sinceros ao 
    vetor de comparacao, indo da maior quantidade de guardioes sinceros, para 
    a menor quantidade*/
    for(t = 0; t < nguard; t++, m--){
        
        c[t] = m;
            
    }
    
    /*Verifica a probabilidade de cada quantidade de guardioes sinceros ser 
    possivel*/
    for(t = 0; t < nguard; t++){    
        
        for(i = 0; i < nguard; i++){
            
            if(c[t] >= a[i] && c[t] <= b[i]){
                
                d[t]++;
                
            }
        }   
        
    }
    
    /*Define quais sao os cenarios de guardioes sinceros mais consistentes*/
    for(t = 0; t < nguard; t++){
        
        if(d[t] == c[t]){
            
            e[t] = d[t];
            
        }
        
    }
    
    /*Dentre os cenarios mais consistentes, define qual e o que possui o maior 
    numero possivel de guardioes sinceros*/
    for(t = 0; t < nguard; t++){
        
        if(e[t] != 0){
                                    
            if(e[t] > sinc){
                
                sinc = e[t];
                
            }
            
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