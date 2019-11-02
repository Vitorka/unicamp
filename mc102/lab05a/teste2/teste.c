#include <stdio.h>

int main(){
    
    char palavra1[21], palavra2[21];
    int i, j, x = 0, y = 0, d = 0, numero = 0;

        
        scanf("%s", palavra1); 
        scanf("%s", palavra2);
        
        for(i = 0; palavra1[i] != '\0'; i++) {
            
            numero++;
            
        }
        
        for(j = 0, i = 0; palavra2[j] != '\0'; j++) {
            
            x = palavra1[i] - 'a';
            y = palavra2[j] - 'a';
            
            if(x == y) {
                
                i++;
                d++;    
            }
            
        }
        
        if(d == numero) {
            
            printf("Sim\n");
            
        } else {
            
            printf("Nao\n");
            
        }
        
    
    
    return 0;
    
}