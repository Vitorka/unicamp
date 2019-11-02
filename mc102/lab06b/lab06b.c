/*Nome: Vitor Kaoru Aoki
  RA: 178474
*/

#include <stdio.h>

/*O programa, dada uma matriz que representa o recinto onde se encontram os 
Jedis, calcula o tempo necessario para preencher todo o espaço com o gas 
venenoso e, caso nao seja possivel preencher todo o recinto, avisa que os Jedis 
podem estar vivos*/
int main()
{
    int recinto[100][100], tempo = 0, contador = 0, intox = 1, lin, col, i, j, 
    aspersor, gas_tox;
    
    scanf("%d %d", &lin, &col);
    
    for(i = 0; i < lin; i++) 
    {    
        for(j = 0; j < col; j++) 
        {
            scanf("%d", &recinto[i][j]);
        }
    }
    
    /*Conta todas as posicoes possiveis onde o gas pode atingir*/
    for(i = 0; i < lin; i++)
    {    
        for(j = 0; j < col; j++)
        {       
            if(recinto[i][j] == 0) 
            {
                contador++;
            }
        }
    }
    
    /*Procura na matriz-recinto os pontos onde estao os aspersores e calcula o 
    tempo necessario para que o gas venenoso atinja o maximo de espacos 
    possiveis. A variavel intox representa uma flag que indica se todas as 
    regioes possiveis de serem intoxicadas, foram intoxicadas*/
    for(aspersor = 2, gas_tox = 3; intox == 1; tempo++, aspersor++, gas_tox++) 
    {   
        intox = 0;
        
        for(i = 0; i < lin; i++)
        {                
            for(j = 0; j < col; j++) 
            {               
                /*Identificado o aspersor, verifica se as regioes onde eh 
                possivel que ele contamine, podem ser contaminadas*/
                if(recinto[i][j] == aspersor) 
                {                     
                    if((recinto[i - 1][j] == 0) && (i - 1 >= 0)) 
                    { 
                        recinto[i - 1][j] = gas_tox;
                        contador--;
                        intox = 1;
                    }
                    
                    if((recinto[i + 1][j] == 0) && (i + 1 < lin)) 
                    {
                        recinto[i + 1][j] = gas_tox;
                        contador--;
                        intox = 1;
                    }
                    
                    if((recinto[i][j - 1] == 0) && (j - 1 >= 0)) 
                    {
                        recinto[i][j - 1] = gas_tox;
                        contador--;
                        intox = 1;
                    }
                    
                    if((recinto[i][j + 1] == 0) && (j + 1 < col)) 
                    {
                        recinto[i][j + 1] = gas_tox;
                        contador--;
                        intox = 1;
                    }
                }
            }
        }
    }
    
    if(contador == 0) 
    {
        printf("Tempo = %d\n", tempo);
    } 
    else 
    {
        printf("Perigo: Jedis podem estar vivos\n");
    }
    return 0;
}