/*Nome: Vitor Kaoru Aoki
 * RA: 178474
 */

#include <stdio.h>

/*O programa roda o jogo Walk-Bot. Tem como objetivo testar todas as 
possibilidades de caminhos realizadas pelo robo, de acordo com um tabuleiro 
pre-determinado pelo jogador. Nesses testes, verifica se o robo conseguiu sair 
do tabuleiro, se ele caiu em uma armadilha, ou se acabou entrando em um loop 
infinito*/
int main(){
    
    int i, j, k, l, inicio_jogo, linhas, colunas, passo = 0, loop = 0, 
    parada = 0, tabuleiro2[50][50];
    char tabuleiro[50][51];
    
    scanf("%d %d", &linhas, &colunas);
    
    scanf(" ");
    for(i = 0; i < linhas; i++)
    {
        scanf("%s", tabuleiro[i]);
    }
    
    /*Zera a matriz auxiliar utilizada para contar o tamanho do loop*/
    for(k = 0; k < linhas; k++)
    {
        for(l = 0; l < colunas; l++)
        {
            tabuleiro2[k][l] = 0;
        }
    }
    
    for(i = 0, j = 0, inicio_jogo = 0; inicio_jogo < linhas; parada = 0, 
    passo = 0)
    {
        /*Continua rodando o jogo ate que uma das condicoes para que ele 
        termine, seja verdadeira*/
        while(parada == 0)
        {
            if((tabuleiro[i][j] == 'R') && (j != colunas - 1))
            {
                j++;
                passo++;
            }
            else if((tabuleiro[i][j] == 'L') && (j != 0))
            {
                j--;
                passo++;
            }
            else if((tabuleiro[i][j] == 'D') && (i != linhas - 1))
            {
                i++;
                passo++;
            }
            else if((tabuleiro[i][j] == 'U') && (i != 0))
            {
                i--;
                passo++;
            }
            /*Condicao de termino do jogo, caso o robo encontre uma armadilha*/
            else if(tabuleiro[i][j] == 'X')
            {
                parada = 1;
            }
            /*Condicao de termino do jogo, caso o robo consiga sair do 
            tabuleiro*/
            if((j == colunas - 1) && (tabuleiro[i][j] == 'R'))
            {
                parada = 2;
            }
            /*Matriz auxiliar que guarda o caminho realizado pelo robo, para a 
            contagem do tamanho do loop, caso ele ocorra. Marca como 1, o 
            caminho realizado pelo robo antes de entrar no loop, e como 2, o 
            caminho realizado por ele no loop. Quando o caminho realizado por 
            ele no loop estiver registrado, termina o jogo*/
            if(tabuleiro2[i][j] != 2)
            {
                tabuleiro2[i][j]++;
            }
            else
            {
                parada = 3;
            }
            
        }
        if(parada == 2)
        {
            printf("Saiu em (%d,%d) apos %d passo(s)\n", i + 1, j + 1, passo);
        }
        else if(parada == 1)
        {
            printf("Armadilha em (%d,%d) apos %d passo(s)\n", i + 1, j + 1, 
            passo);
        }
        else if(parada == 3)
        {
            loop = 0;
            /*Percorre a matriz auxiliar para a contagem do tamanho do loop*/
            for(k = 0; k < linhas; k++)
            {
                for(l = 0; l < colunas; l++)
                {
                    if(tabuleiro2[k][l] == 2)
                    {
                        loop++;
                    }
                }
            }
            printf("Loop de tamanho %d\n", loop);
        }
        j = 0;
        inicio_jogo++;
        i = inicio_jogo;
        /*Zera a matriz auxiliar para rodar o jogo novamente*/
        for(k = 0; k < linhas; k++)
        {
            for(l = 0; l < colunas; l++)
            {
                tabuleiro2[k][l] = 0;
            }
        }
    }
            
    return 0;
}