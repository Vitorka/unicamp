#include <stdio.h>

int main() {
    
    char palavra[81], aux, aux2;
    int i = 0, j, x;
    
    printf("Entre com uma palavra: ");
    
    scanf("%s", palavra);
    
    while(palavra[i] != '\0') {
        
        i++;
        
    }
    
    palavra[i] = '\0';
    
    for(j = 0, x = i - 1; j < x; j++, x--) {
            
        aux = palavra[x];
        aux2 = palavra[j];    
        palavra[j] = aux;
        palavra[x] = aux2;
        
    }
    
    printf("A palavra invertida e: %s\n", palavra);
    
    return 0;
    
}