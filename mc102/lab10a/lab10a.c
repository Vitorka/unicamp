/*Nome: Vitor Kaoru Aoki   
  RA: 178474
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){ 
    
    int i, j, k, num_palv, min_ocorre, tam_min, tam_max, tamanho, iguais, aux, 
    palavra_verificada;
    int *ocorrencia, *posicao;
    char *leitor, **palavras;
    
    scanf("%d %d %d %d", &num_palv, &min_ocorre, &tam_min, &tam_max);

    leitor = malloc((tam_max + 1) * sizeof(char));
    
    posicao = malloc((num_palv) * sizeof(int));
    
    ocorrencia = malloc((num_palv) * sizeof(int));
    
    palavras = malloc((num_palv) * sizeof(char *));
    for(i = 0; i < (num_palv); i++)
    {
        palavras[i] = malloc((tam_max + 1) * sizeof(char));
    }
    
    /*Zera o vetor que conta o numero de ocorrencias*/
    for(i = 0; i < (num_palv); i++)
    {
        ocorrencia[i] = 0;
    }
    
    /*Inicializa a matriz de palavras com '\0'*/
    for(i = 0; i < num_palv; i++)
    {
        for(j = 0; j < (tam_max + 1); j++)
        {
            palavras[i][j] = '\0';
        }
    }
    
    /*Armazena a primeira palavra do texto para poder iniciar as comparacoes 
    das palavras seguintes*/
    scanf(" ");
    scanf("%s", *palavras);
    ocorrencia[0]++;
    posicao[0] = 0;
    j = 0;
    
    /*Verifica se a palavra lida possui o tamanho minimo exigido e se ela ja 
    apareceu no texto. Caso ainda nao tenha aparecido eh armazenada, caso ja 
    tenha aparecido eh apenas contabilizada*/
    while(*leitor != '*')
    {   
        scanf(" ");
        scanf("%s", leitor);
        
        tamanho = strlen(leitor);
        palavra_verificada = 0;
        
        if(tamanho >= tam_min)
        {
            /*Verifica na matriz onde sao armazenadas as palavras, se a palavra 
            lida ja apareceu no texto*/
            for(i = 0; palavra_verificada == 0; i++)
            {
                iguais = strcmp(leitor, palavras[i]);
                
                if(iguais == 0)
                {
                    ocorrencia[i]++;
                    palavra_verificada = 1;
                }
                /*Armazena a posicao de uma nova palavra armazenada, em um 
                vetor de posicoes, para posterior ordenacao delas*/
                else if(*palavras[i + 1] == '\0')
                {
                    strncpy(palavras[i + 1], leitor, tamanho);
                    ocorrencia[i + 1]++;
                    posicao[i + 1] = (i + 1);
                    palavra_verificada = 1;
                }
            }
        }
    }
    
    /*Ordena as palavras palavras armazenadas em ordem decrescente de acordo 
    com seu numero de ocorrencias*/
    for(i = 0; ocorrencia[i] != 0; i++)
    {
        j = i;
        
        for(k = i + 1; ocorrencia[k] != 0; k++)
        {
            if(ocorrencia[j] < ocorrencia[k])
            {
                j = k;
            }
            
        }
        /*Ordena o vetor de ocorrencias*/
        aux = ocorrencia[j];
        ocorrencia[j] = ocorrencia[i];
        ocorrencia[i] = aux;
        
        /*Juntamente com o vetor de ocorrencias, ordena as palavras 
        correspondentes a cada ocorrencia, por meio do vetor de posicoes*/
        aux = posicao[i];
        posicao[i] = posicao[j];
        posicao[j] = aux;
    }
    
    /*Ordena lexicograficamente as palavras*/
    for(i = 0; ocorrencia[i] >= min_ocorre; i++)
    {
        if(ocorrencia[i] == ocorrencia[i + 1])
        {
            for(j = i + 1; ocorrencia[j] == ocorrencia[i]; j++)
            {
                iguais = strcmp(palavras[posicao[i]], palavras[posicao[j]]);
                
                if(iguais > 0)
                {
                    aux = posicao[i];
                    posicao[i] = posicao[j];
                    posicao[j] = aux;
                }
            }
        }
    }
    
    for(i = 0; (palavras[i] != '\0') && (ocorrencia[i] != 0); i++)
    {
        if(ocorrencia[i] >= min_ocorre)
        {
            printf("%s ", palavras[posicao[i]]);
            printf("%d\n", ocorrencia[i]);
        }
    }
    
    free(ocorrencia);
    free(posicao);
    free(leitor);
    
    for(i = 0; i < num_palv; i++)
    {
        free(palavras[i]);
    }
    free(palavras);
    
    return 0;
}
    