/*Nome: Vitor Kaoru Aoki   
  RA: 178474
*/

#include <stdio.h>
#include <stdlib.h>
#define max_jog 50

/*O programa, a partir das notas dadas a cada jogador participante da pelada, 
escolhe quem serao os capitaes, de acordo com a media de nota de cada jogador e 
a partir desses capitaes sao escolhidos os jogadores de cada time, a partir das 
notas de cada "peladeiro"*/
int main()
{    
    int i, j, k, l, m, n, p, num_jog, num_times, times[10][25], jog_total, 
    contador = 0;
    float notas[max_jog][max_jog], medias[max_jog];
    
    scanf("%d %d", &num_jog, &num_times);
    
    jog_total = num_jog;
    
    for(i = 0; i < num_jog; i++)
    {
        for(j = 0; j < num_jog; j++)
        {
            scanf("%f", &notas[i][j]);
        }
    }
    
    for(i = 0; i < num_jog; i++)
    {
        medias[i] = 0;
    }
    
    /*Calcula a media de nota de cada jogador*/
    for(j = 0; j < num_jog; j++)
    {
        for(i = 0; i < num_jog; i++)
        {
            medias[j] += notas[i][j]/num_jog;
        }
    }
    
    /*Verfica quais sao os jogadores com as maiores medias, para a definicao 
    dos capitaes. O numero de capitaes eh definido de acordo com o numero de 
    times*/
    for(i = 0; i < num_times; i++)
    {
        for(j = 1, k = 0; j < num_jog; j++)
        {
            if(medias[k] >= medias[j])
            {
                k = k;
            }
            else
            {
                k = j;
            }
        }
        times[i][0] = k;
        jog_total--;
        
        /*Apos o capitao ser escolhido, elimina a possibilidade dele ser 
        escolhido novamente como capitao e como jogador de um outro time*/
        for(l = 0; l < num_jog; l++)
        {
            notas[l][k] = - 1;
        }
        medias[k] = - 1;
    }
    
    /*Escolhe os jogadores para cada time, a partir das notas dadas a eles*/
    for(i = 0, j = 1; jog_total != 0; i++)
    {
        l = times[i][0];
        
        for(m = 1, n = 0; m < num_jog; m++)
        {
            if(notas[l][n] >= notas[l][m])
            {
                n = n;
            }
            else
            {
                n = m;
            }
        }
        
        times[i][j] = n;
        
        /*Exclui a possibilidade do jogador escolhido, ser escolhido novamente 
        por outro capitao*/
        for(p = 0; p < num_jog; p++)
        {
            notas[p][n] = - 1;
        }
        
        contador++;
        jog_total--;
        
        /*Condicional que garante que os capitaes irao escolher os jogadores 
        alternadamente, voltando ao capitao que fez a primeira escolha, ao fim 
        de cada rodada de escolhas*/
        if(contador == num_times)
        {
            i = - 1;
            j++;
            contador = 0;
        }
    }
    
    
    for(i = 0; i < num_times; i++)
    {
        printf("Time %d:", i + 1);
        for(j = 0; (j < num_jog/num_times); j++)
        {
            printf(" %d", times[i][j] + 1);
        }
        printf("\n");
    }
    
    return 0;
}
    