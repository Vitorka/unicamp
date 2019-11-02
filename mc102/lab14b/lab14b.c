/*Nome: Vitor Kaoru Aoki   
  RA: 178474*/

#include <stdio.h>
#include <stdlib.h>

void influencia(int **mat_infl, int **temp, int custo[], int aux, int num_parl,
                int *custo_final, int tam_part)
{
    int i, j, contador = 0, preco = 0;
    
    for(i = 0; i < num_parl; i++)
    {
        temp[1][i] = 0;
    }
    
    /*Contabiliza os parlamentares do grupo sem suas influencias*/
    for(j = 0; j < aux; j++)
    {
        contador++;
    }
    
    /*Verifica na matriz de influencias quantos parlamentares cada parlamentar 
    pode levar, e elimina a possibilidade dos parlamentares escolhidos, serem 
    escolhidos novamente*/
    for(i = 0; i < aux; i++)
    {
        if(temp[1][temp[0][i]] == 0)
        {
            for(j = 0; j < num_parl; j++)
            {   
                if((mat_infl[temp[0][i]][j] == 1) && (temp[0][i] != j) &&
                   (temp[1][j] == 0))
                {
                    contador++;
                    temp[1][j] = 1;
                }
            }
        }
        temp[1][temp[0][i]] = 1;
    }
    
    /*Contabiliza o custo total do grupo de parlamentares escolhidos*/
    for(i = 0; i < aux; i++)
    {
        preco += custo[temp[0][i]];
    }
    
    /*Verifica se o grupo de parlamentares possue o tamanho minimo necessario 
    para o partido*/
    if(contador >= tam_part)
    {
        if(*custo_final == 0)
        {
            *custo_final = preco;
        }
        else if(preco < *custo_final)
        {
            *custo_final = preco;    
        }
    }
    
}

void combinacoes(int **mat_infl, int custo[], int **temp, int num_parl, 
                 int aux, int next, int size, int *custo_final, int tam_part)
{
    int i;
    
    /*Se a combinacao possivel foi atingida verifica se os parlamentares 
    escolhidos custam o menor preco possivel e respeitam a quantidade minima de 
    parlamentares no partido*/
    if(size == aux)
    {
        influencia(mat_infl, temp, custo, aux, num_parl, custo_final, 
                   tam_part);
    }
    /*Caso contrario, continua montando as combinacoes*/
    else
    {
        for(i = next; i < num_parl; i++) 
        {
            temp[0][size] = i;
            combinacoes(mat_infl, custo, temp, num_parl, aux, i + 1, size + 1, 
                        custo_final, tam_part);
        }
    }
}

/*O programa escolhe a melhor combinacao de compra possivel (o menor custo 
para montar um partido com no minimo o numero de candidatos necessarios) entre 
o numero de parlamentares dados, o preco de cada um e do numero minimo de 
parlamentares necessarios para o partido*/
int main()
{
    int i, j, num_parl, tam_part, aux, custo_final = 0;
    int *custo, **mat_infl, **temp;
    
    scanf("%d %d", &num_parl, &tam_part);
    
    custo = malloc(num_parl * sizeof(int));
    
    temp = malloc(2 * sizeof(int *));
    for(i = 0; i < 2; i++)
    {
        temp[i] = malloc(num_parl * sizeof(int));
    }
    
    mat_infl = malloc(num_parl * sizeof(int *));
    for(i = 0; i < num_parl; i++)
    {
        mat_infl[i] = malloc(num_parl * sizeof(int));
    }
    
    for(i = 0; i < num_parl; i++)
    {
        scanf("%d", &custo[i]);
    }
    
    for(i = 0; i < num_parl; i++)
    {
        for(j = 0; j < num_parl; j++)
        {
            scanf("%d", &mat_infl[i][j]);
        }
    }
    
    for(i = 0; i < 2; i++)
    {
        for(j = 0; j < num_parl; j++)
        {
            temp[i][j] = 0;
        }
    }
    
    /*Chama a funcao que realiza todas combinacoes possiveis de compra de 
    parlamentares*/
    aux = num_parl;
    while(aux != 0)
    {
        combinacoes(mat_infl, custo, temp, num_parl, aux, 0, 0, &custo_final,
                    tam_part);
        aux--;
    }
    
    printf("%d\n", custo_final);
    
    free(custo);
    
    for(i = 0; i < 2; i++)
    {
        free(temp[i]);
    }
    free(temp);
    
    for(i = 0; i < num_parl; i++)
    {
        free(mat_infl[i]);
    }
    free(mat_infl);
    

    return 0;
}
    