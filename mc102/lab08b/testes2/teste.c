#include <stdio.h>
#include <math.h>

int main()
{
    
    int i , j, linhas, colunas;
    float matriz2[100][100], matriz[100][100];
    
    scanf("%d %d", &linhas, &colunas);
    
    for(i = 0; i < linhas; i++)
    {
        for(j = 0; j < colunas; j++)
        {
            scanf("%f", &matriz[i][j]);
        }
    }
    
    for(i = 0; i < linhas; i++)
    {
        for(j = 0; j < colunas; j++)
        {
            matriz2[i][j] = 0;
        }
    }
    
    for(i = 0, j = 0; i < linhas - 2; i++, j = 0)
    {
        for(j = 0; j < colunas - 2; j++)
        {
            /*Verticais e horizontais*/
            matriz2[i + 1][j + 1] += ((2 * matriz[i][j + 1]) / 16);
            matriz2[i + 1][j + 1] += ((2 * matriz[i + 2][j + 1]) / 16);
            matriz2[i + 1][j + 1] += ((2 * matriz[i + 1][j]) / 16); 
            matriz2[i + 1][j + 1] += ((2 * matriz[i + 1][j + 2]) / 16);
            
            /*Diagonais*/
            
            matriz2[i + 1][j + 1] += ((1 * matriz[i][j]) / 16);
            matriz2[i + 1][j + 1] += ((1 * matriz[i + 2][j]) / 16);
            matriz2[i + 1][j + 1] += ((1 * matriz[i][j + 2]) / 16);
            matriz2[i + 1][j + 1] += ((1 * matriz[i + 2][j + 2]) / 16);
            
            /*Ponto*/
            
            matriz2[i + 1][j + 1] += ((4 * matriz[i + 1][j + 1]) / 16);
        }
    }
    
    for(i = 1; i < linhas - 1; i++)
    {
        for(j = 1; j < colunas - 1; j++)
        {
            matriz[i][j] = matriz2[i][j];
        }
    }
            
    printf("\n");
    for(i = 0; i < linhas; i++)
    {
        for(j = 0; j < colunas; j++)
        {
            printf("%f ", (int)floor(matriz[i][j]));
        }
        printf("\n");
    }
    return 0;
}