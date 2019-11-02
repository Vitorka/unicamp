#include <stdio.h>

int main() {
    
    char palavra1[21], palavra2[21];
    int ncarac[128], j, anagrama = 1;
    
    printf("Entre com duas palavras: ");
    
    scanf("%s %s", palavra1, palavra2);
    
    for(j = 0; j < 128; j++){
        
        ncarac[j] = 0;
        
    }
    
    for(j = 0; palavra1[j] != '\0'; j++){
        
        
        ncarac[(int) palavra1[j]]++;
        
    }
    
    for(j = 0; palavra2[j] != '\0'; j++){
        
        
        ncarac[(int) palavra2[j]]--;
        
    }
    
    for(j = 0; j < 128; j++){
        
        if(ncarac[j] != 0){
            
            anagrama = 0;
            
        }
        
    }
    
    if(anagrama == 0){
        
        printf("Não são anagramas\n");
        
    } else {
        
        printf("São anagramas\n");
        
    }
    
    return 0;
    
}
        