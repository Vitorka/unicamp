/* Karim Michel
 * RA:171395
 * Laboratório Nº 16. Peso 2. */


#include <stdio.h>
#include <stdlib.h>

void modifica_cor(int inicial, int x, int y, int **imagem, int nova_cor, 
                  int linhas, int colunas) {
    if((x>=0) && (y>=0) && (x<=linhas-1) && (y<=colunas-1) && 
        (inicial == imagem[x][y])) {
        imagem[x][y] = nova_cor;
        modifica_cor(inicial, x-1,y-1, imagem, nova_cor, linhas, colunas);
        modifica_cor(inicial, x-1, y, imagem, nova_cor, linhas, colunas);
        modifica_cor(inicial, x-1, y+1, imagem, nova_cor, linhas, colunas);
        modifica_cor(inicial, x, y-1, imagem, nova_cor, linhas, colunas);
        modifica_cor(inicial, x, y+1, imagem, nova_cor, linhas, colunas);
        modifica_cor(inicial, x+1, y-1, imagem, nova_cor, linhas, colunas);
        modifica_cor(inicial, x+1, y, imagem, nova_cor, linhas, colunas);
        modifica_cor(inicial, x+1, y+1, imagem, nova_cor, linhas, colunas);
    }
}
    
int main(int argc, char *argv[]) {
    FILE *image_pmg;
    char nome[5];
    int linhas, colunas;
    int max_cinza;
    int **imagem;
    int i;
    int j;
    int x, y, nova_cor, inicial;
    
    scanf("%d", &x);
    scanf("%d", &y);
    scanf("%d", &nova_cor);
    
    image_pmg = fopen(argv[1], "r");    
    
    fscanf(image_pmg, "%s", nome);
    fscanf(image_pmg, "%d", &colunas);
    fscanf(image_pmg, "%d", &linhas);
    fscanf(image_pmg, "%d", &max_cinza);
    
    imagem = malloc(linhas * sizeof(int*));
    for(i=0;i<linhas;i++) {
        imagem[i]=malloc(colunas * sizeof(int));
    }
    
    for(i=0;i<linhas;i++) {
        for(j=0;j<colunas;j++) {
            fscanf(image_pmg, "%d", &imagem[i][j]);
        }
    }
    
    inicial=imagem[x][y];
    modifica_cor(inicial, x, y, imagem, nova_cor, linhas, colunas);
    
    
    printf("%s\n", nome);
    printf("%d %d\n", colunas, linhas);
    printf("%d\n", max_cinza);
    for(i=0;i<linhas;i++) {
        for(j=0;j<colunas;j++) {
            printf("%d ", imagem[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}