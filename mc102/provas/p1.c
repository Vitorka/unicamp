#include <stdio.h>

int main() {
    
    char correta[81], inversa[81];
    int i = 0, j, x = 0;
    
    printf("Entre com uma palavra: ");
    
    scanf("%s", correta);
    
    while(correta[i] != '\0'){
        
        i++;
        
    }
    
    inversa[i] = '\0';
    
    for(j = 0, x = i - 1; j < i; j++, x--) {
        
        inversa[j] = correta[x];
        
    }
    
    printf("A palavra inversa é: %s\n", inversa);
    
    return 0;
    
}