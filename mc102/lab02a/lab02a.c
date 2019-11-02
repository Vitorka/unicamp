/*Nome: Vitor Kaoru Aoki
  RA: 178474
*/

#include <stdio.h>

int main(){

    char x;
    int y, a, b = 0, c = 0;
    float d;
        
    scanf("%c", &x);
    
    /*Condicao para o aluno que nao cursou nenhuma disciplina*/
    if(x == '*'){
        
        printf("CR = Indefinido\n");
        
    }
    else{
    
    /*Atribuicao dos pesos para as respectivas notas*/    
    while(x != '*') {
        
        scanf("%d", &y);
    
        if(x == 'A'){
        
            a = 4;
        
        }
        else if(x == 'B'){
        
            a = 3;
        
        }   
        else if(x == 'C'){
        
            a = 2;
        
        }
        else if(x == 'D'){
       
            a = 1;
       
        }
        else if(x == 'E'){
       
            a = 0;
       
        }
                      
        /*Mutiplicacao dos pesos com os creditos*/
        b += a * y;
        /*Soma de todos os creditos*/
        c += y;
        /*Calculo do CR final*/
        d = (float)b / (float)c;
                                       
        scanf(" %c", &x);
    }
    
    printf("CR = %.4f\n", d);
        
    }
   
    return 0;
    
}
    
       
  
