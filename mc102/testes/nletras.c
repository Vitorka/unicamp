#include <stdio.h>

int main(){
    
    char letra;
    int nletras = 0;
    
    printf("Digite uma frase: ");
    
    scanf("%c", &letra);
                
        while(('A' <= letra && letra <= 'Z') || ('a' <= letra && letra <= 'z') 
|| (letra != '\n')){
            
            if(('A' <= letra && letra <= 'Z') || ('a' <= letra && letra <= 
'z')){
                
                nletras ++;
                
            }
            
            scanf("%c", &letra);
        }
        
    printf("Numero de letras = %d\n", nletras);
    
    
    return 0;
    
}