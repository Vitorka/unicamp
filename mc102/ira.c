#include <stdio.h>
#include <stdlib.h>

void convoluc(int **matriz, int **aux, int convolucao[][3], int linhas, 
              int colunas, int d)
{
    int i, j;
    
    for(i = 1; i < linhas - 1; i++)
    {
        for(j = 1; j < colunas - 1; j++)
        {
            aux[i][j] = 0;
            
            aux[i][j] += (int)(matriz[i - 1][j - 1] * convolucao[0][0]) / d;
            aux[i][j] += (int)(matriz[i - 1][j] * convolucao[1][0]) / d;
            aux[i][j] += (int)(matriz[i - 1][j + 1] * convolucao[2][0]) / d;
            aux[i][j] += (int)(matriz[i][j - 1] * convolucao[0][1]) / d;
            aux[i][j] += (int)(matriz[i][j] * convolucao[1][1]) / d;
            aux[i][j] += (int)(matriz[i][j + 1] * convolucao[2][1]) / d;
            aux[i][j] += (int)(matriz[i + 1][j - 1] * convolucao[0][2]) / d;
            aux[i][j] += (int)(matriz[i + 1][j] * convolucao[1][2]) / d;
            aux[i][j] += (int)(matriz[i + 1][j + 1] * convolucao[2][2]) / d;
        }
    }
    
    for(i = 1; i < linhas - 1; i++)
    {
        for(j = 1; j < colunas - 1; j++)
        {
            matriz[i][j] = aux[i][j];
        }
    }
}

int main(int argc, char *argv[]) 
{   
    FILE *arqin, *arqin2;
    char nome[5];
    int colunas, linhas, max, divisor;
    int **matriz, convolucao[3][3], **aux;
    int i, j;
    
    arqin = fopen(argv[1], "r");
    
    fscanf(arqin, "%s", nome);
    fscanf(arqin, "%d", &colunas);
    fscanf(arqin, "%d", &linhas);
    fscanf(arqin, "%d", &max);
    
    matriz = malloc(linhas * sizeof(int*));
    
    for(i = 0; i < linhas; i++)
    {
        matriz[i] = malloc(colunas * sizeof(int));
    }
    
    aux = malloc(linhas * sizeof(int *));
    for(i = 0; i < linhas; i++)
    {
        aux[i] = malloc(colunas * sizeof(int));
    }
    
    for(i = 0; i < linhas; i++)
    {
        for(j = 0; j < colunas; j++)
        {
            fscanf(arqin, "%d", &matriz[i][j]);
        }
    }
    
    arqin2 = fopen(argv[2], "r");
    
    fscanf(arqin2, "%d", &divisor);
    
    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            fscanf(arqin2, "%d", &convolucao[i][j]);
        }
    }
    
    /*convoluc(matriz, aux, convolucao, linhas, colunas, divisor);*/
    
    printf("%s\n", nome);
    printf("%d %d\n", colunas, linhas);
    printf("%d\n", max);
    
    for(i = 0; i < linhas; i++)
    {
        for(j = 0; j < colunas; j++)
        {
            if(matriz[i][j] > max)
            {
                printf("%d ", max);
            }
            else if(matriz[i][j] < 0)
            {
                printf("%d ", 0);
            }
            else
            {
                printf("%d ", matriz[i][j]);
            }
        }
        printf("\n");
    }
    
    fclose(arqin);
    fclose(arqin2);
    
    return 0;
}
