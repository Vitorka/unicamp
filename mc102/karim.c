#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *image_pmg;
    char nome[5];
    int linhas, colunas;
    int max_cinza;
    int **imagem;
    int i;
    int j;
    int x, y, nova_cor;
    
    scanf("%d", &x);
    printf("x = %d\n", x);
    scanf("%d", &y);
    scanf("%d", &nova_cor);
    
    image_pmg = fopen(argv[1], "r");    
    
    fscanf(image_pmg, "%s", nome);
    fscanf(image_pmg, "%d", &linhas);
    fscanf(image_pmg, "%d", &colunas);
    fscanf(image_pmg, "%d", &max_cinza);
    
    printf("%s\n", nome);
    
    imagem = malloc(linhas * sizeof(int*    ));
    for(i = 0; i < linhas; i++)
    {
        imagem[i] = malloc(colunas * sizeof(int));
    }
    
    
    for(i = 0; i < linhas; i++)
    {
        for(j = 0; j < colunas; j++)
        {
            fscanf(image_pmg, "%d", &imagem[i][j]);
        }
    }
    
    for(i = 0; i < linhas; i++)
    {
        for(j = 0; j < colunas; j++)
        {
            printf("%d ", imagem[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}