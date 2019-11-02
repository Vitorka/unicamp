#include <stdio.h>

int main(){
    
    int recinto[100][100], lin, col, i, j, contador = 0, parede_coluna = 0,     
    parede_linha = 0, parada = 0, parada2 = 0;
    
    scanf("%d %d", &lin, &col);
    
    for(i = 0; i < lin; i++) {
        
        for(j = 0; j < col; j++) {    
            scanf("%d", &recinto[i][j]);
        }
    }
    
    for(i = 0; i < lin; i++) {
        
        for(j = 0; j < col; j++) {    
            
            if(recinto[i][j] == 0) {
                contador++;
            }
        }
    }
    
    /*Verifica se ha uma parede nas colunas*/   
    for(j = 1; (j < col - 1) && (parede_coluna != lin); j++) {
        parada = 0;
        for(i = 0; i < lin; i++) {
            
            if(recinto[i][j] == 1) {
                parada++;
            }
            
        }
        
        if(parada == lin) {
            parede_coluna = parada;
        }
        printf("parada = %d\n", parada);
    }
    
    /*Verifica se ha uma parede nas linhas*/
    for(i = 1; (i < lin - 1) && (parede_linha != col); i++) {
        parada2 = 0;
        for(j = 0; j < col; j++) {
            
           if(recinto[i][j] == 1) {
               parada2++;
           }
           
        }
        
        if(parada2 == col) {
            parede_linha = parada2;
        }
        printf("parada2 = %d\n", parada2);
    }
    
    printf("parede_coluna = %d\n", parede_coluna);
    printf("parede_linha = %d\n", parede_linha);
    printf("contador = %d\n", contador);
    return 0;
}