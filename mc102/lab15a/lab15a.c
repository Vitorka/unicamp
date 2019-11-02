/*Nome: Vitor Kaoru Aoki
  RA: 178474
*/

#include <stdio.h>
#define max 20

int percurso(int tabuleiro[max][max], int tab_aux[max][max], int lin, int col,
             int linhas, int colunas, int energia)
{
    int l, aux[4];
    
    /*Inicializa o vetor aux, que armazena se algum dos caminhos possiveis 
    levou a saida do tabuleiro, sendo essa saida, indicada por 0*/
    for(l = 0; l < 4; l++)
    {
        aux[l] = 2;
    }
    
    /*Caso o robo encontre uma armadilha ou acabe sua energia, retorna 1, 
    indicando que ele "morreu"*/
    if((energia == 0) || (tabuleiro[lin][col] == 0)) /*morreu*/
    {
        return 1;
    }
    else
    {   
        /*Indica na matriz auxiliar do tabuleiro, que o robo ja passou por 
        aquela casa*/ 
        tab_aux[lin][col] = 1;
        
        /*A partir do numero lido, veirifica a partir da representacao binaria 
        desse numero, se ele pode ir para a esquerda*/
        if((tabuleiro[lin][col] & (1 << 0)) && (energia != 0) && 
           (tab_aux[lin][col - 1] == 0))
        {
            aux[0] = percurso(tabuleiro, tab_aux, lin, col - 1, 
                              linhas, colunas, energia - 1);
            tab_aux[lin][col - 1] = 0;
        }
        /*A partir do numero lido, veirifica a partir da representacao binaria 
        desse numero, se ele pode ir para baixo*/
        if((tabuleiro[lin][col] & (1 << 1)) && (energia != 0) &&
           (tab_aux[lin + 1][col] == 0))
        {
            aux[1] = percurso(tabuleiro, tab_aux, lin + 1, col, 
                              linhas, colunas, energia - 1);
            tab_aux[lin + 1][col] = 0;
        }
        /*A partir do numero lido, veirifica a partir da representacao binaria 
        desse numero, se ele pode ir para a direita*/
        if((tabuleiro[lin][col] & (1 << 2)) && (energia != 0)) 
        {
            if(col == colunas - 1)
            {
                return 0;
            }
            else if(tab_aux[lin][col + 1] == 0)
            {
                aux[2] = percurso(tabuleiro, tab_aux, lin, col + 1, 
                                  linhas, colunas, energia - 1);
                tab_aux[lin][col + 1] = 0;
            }
        }
        /*A partir do numero lido, veirifica a partir da representacao binaria 
        desse numero, se ele pode ir para a cima*/
        if((tabuleiro[lin][col] & (1 << 3)) && (energia != 0) &&
           (tab_aux[lin - 1][col] == 0)) /*cima*/
        {
            aux[3] = percurso(tabuleiro, tab_aux, lin - 1, col, 
                              linhas, colunas, energia - 1);
            tab_aux[lin - 1][col] = 0;
        }
        
        /*Caso algum dos caminhos leve ele a saida do tabuleiro, retorna 0, 
        indicando que o caminho eh valido*/
        if((aux[0] == 0) || (aux[1] == 0) || (aux[2] == 0) || (aux[3] == 0))
        {
            return 0;
        }
        else
        {
            return 1;
        }
    }
}

/*O programa eh a continuacao do jogo Walk-Bot, tendo como diferencial a 
possibilidade de mais de um movimento do robo a partir de uma casa, de acordo 
com o numero dessa casa, que indica os caminhos possiveis*/
int main()
{
    int i, j, k, linhas, colunas, energia, caminho;
    int tabuleiro[max][max], tab_aux[max][max];
    
    scanf("%d %d %d", &linhas, &colunas, &energia);
    
    for(i = 0; i < linhas; i++)
    {
        for(j = 0; j < colunas; j++)
        {
            tabuleiro[i][j] = 0;
            tab_aux[i][j] = 0;
        }
    }
    
    for(i = 0; i < linhas; i++)
    {
        for(j = 0; j < colunas; j++)
        {
            scanf("%d", &tabuleiro[i][j]);
        }
    }
    
    /*Verifica se entre todas as entradas possiveis, alguma leva a saida do 
    tabuleiro*/
    for(i = 0; i < linhas; i++)
    {
        caminho = percurso(tabuleiro, tab_aux, i, 0, linhas, colunas, 
                           energia);
        
        if(caminho == 0)
        {
            printf("Sim\n");
        }
        else
        {
            printf("Nao\n");
        }
        
        for(j = 0; j < linhas; j++)
        {
            for(k = 0; k < colunas; k++)
            {
                tab_aux[j][k] = 0;
            }
        }
    }
        
    return 0;
}