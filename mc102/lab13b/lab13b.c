/*Nome: Vitor Kaoru Aoki   
  RA: 178474
*/

#include <stdio.h>
#include <stdlib.h>

/*O programa analisa uma matriz e contabiliza a quantidade de regioes 
homogeneas existentes*/
int verifica_homog(int **matriz, int dimensao, int i, int j)
{
    int k, l, flag = 0;
    int linhas = 0, colunas = 0;
    
    for(k = i; (linhas < dimensao) && (flag == 0); k++, linhas++, colunas = 0)
    {
        for(l = j; (colunas < dimensao) && (flag == 0); l++, colunas++)
        {
            if(matriz[i][j] != matriz[k][l])
            {
                flag = 1;
            }
        }
    }
    
    /*Caso a matriz nao seja homogenea, retorna 0*/
    if(flag == 1)
    {
        return 0;
    }
    /*Caso a matriz seja homogenea, retorna 1*/
    else
    {
        return 1;
    }
}

int quadtree(int **matriz, int dimensao, int j, int k)
{
    int aux, regiao_parcial = 0;
    
    aux = verifica_homog(matriz, dimensao, j, k);
    
    /*Caso a matriz seja homogenea, retorna o valor de aux*/
    if(aux == 1)
    {
        return aux;
    }
    /*Caso nao seja homogenea, chama a funcao quadtree recursivamente, 
    dividindo a matriz em quadrantes*/
    else
    {   
        dimensao = dimensao / 2;
        
        /*Chama a funcao recursivamente para o quadrante 1, e armazena a 
        quantidade de regioes homogeneas existentes nele*/
        regiao_parcial += quadtree(matriz, dimensao, j, k);
        
        /*Chama a funcao recursivamente para o quadrante 2, e armazena a 
        quantidade de regioes homogeneas existentes nele*/
        regiao_parcial += quadtree(matriz, dimensao, j, (k + dimensao));
        
        /*Chama a funcao recursivamente para o quadrante 3, e armazena a 
        quantidade de regioes homogeneas existentes nele*/
        regiao_parcial += quadtree(matriz, dimensao, (j + dimensao), k);
        
        /*Chama a funcao recursivamente para o quadrante 4, e armazena a 
        quantidade de regioes homogeneas existentes nele*/
        regiao_parcial += quadtree(matriz, dimensao, (j + dimensao), 
                                   (k + dimensao));
        
        return regiao_parcial;
    }
}
    
int main()
{
    int i, j, dimensao, **matriz, num_regioes;
    
    scanf("%d", &dimensao);
    
    matriz = malloc(dimensao * sizeof(int*));
    
    for (i = 0; i < dimensao; i++)  
    {
        matriz[i] = malloc(dimensao * sizeof(int));
    }
    
    for(i = 0; i < dimensao; i++)
    {
        for(j = 0; j < dimensao; j++)
        {
            scanf("%d", &matriz[i][j]);
        }
    }
    
    /*Chama a funcao quadtree para que seja contabilizado o numero de regioes 
    homogeneas existentes na matriz*/
    num_regioes = quadtree(matriz, dimensao, 0, 0);
    
    printf("Numero de regioes = %d\n", num_regioes);
    
    for (i = 0; i < dimensao; i++)  
    {
        free(matriz[i]);
    }
    free(matriz);
    
    return 0;
}
    