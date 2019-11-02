/*Nome: Vitor Kaoru Aoki   
  RA: 178474
*/

#include <stdio.h>
#include <stdlib.h>
#define max 50
/*O programa, a partir de uma representacao matricial de um campo de batalha, 
indicando onde se encontram os droids inimigos, descobre qual a posicao mais 
eficiente para colocar a unidade AT-TE. Essa eficiencia segue uma hierarquia, 
sendo a mais alta, o maior numero de droids destruidos, seguida do menor numero 
de disparos, e por ultimo, a menor posicao possivel*/
int main(){
    
    int i, j, k, l, campo_batalha[max][max], linhas, colunas, droids_total = 0, 
    droids = 0, disparos_totais, disparos, pos_lin, pos_col, direca_disparo;
    
    scanf("%d %d", &linhas, &colunas);
    
    for(i = 0; i < linhas; i++)
    {
        for(j = 0; j < colunas; j++)
        {
            scanf("%d", &campo_batalha[i][j]);
        }
    }
    
    /*Verifica todas as posicoes possiveis onde a unidade AT-TE pode ser 
    colocada, a fim de descobrir a mais eficiente*/
    for(i = 0; i < linhas; i++)
    {
        for(j = 0; j < colunas; j++)
        {
            disparos = 0;
            
            if(campo_batalha[i][j] == 0)
            {
                /*Verifica o numero de droids atingidos com o disparo na 
                vertical*/
                for(k = 0, l = j; k < linhas; k++)
                {
                    if(campo_batalha[k][l] == 1)
                    {
                        droids++;
                        direca_disparo = 1;
                    }
                }
                if(direca_disparo == 1)
                {
                    disparos++;
                }
                
                /*Verifica o numero de droids atingidos com o disparo na 
                horizontal*/
                for(k = i, l = 0; l < colunas; l++)
                {
                    if(campo_batalha[k][l] == 1)
                    {
                        droids++;
                        direca_disparo = 2;
                    }
                }
                if(direca_disparo == 2)
                {
                    disparos++;
                }
                                
                /*Verifica o numero de droids atingidos na diagonal 
                (noroeste-sudeste) para cima*/
                for(k = i - 1, l = j - 1; (k >= 0) && (l >= 0); k--, l--)
                {
                    if(campo_batalha[k][l] == 1)
                    {
                        droids++;
                        direca_disparo = 3;
                    }
                }
                /*Verifica o numero de droids atingidos na diagonal 
                (noroeste-sudeste) para baixo*/
                for(k = i + 1, l = j + 1; (k < linhas) && (l < colunas); k++, 
                l++)
                {
                    if(campo_batalha[k][l] == 1)
                    {
                        droids++;
                        direca_disparo = 3;
                    }
                }
                if(direca_disparo == 3)
                {
                    disparos++;
                }
                               
                /*Verifica o numero de droids atingidos na diagonal       
                (nordeste-sudoeste) para cima*/
                for(k = i - 1, l = j + 1; (k >= 0) && (l < colunas); k--, l++)
                {
                    if(campo_batalha[k][l] == 1)
                    {
                        droids++;
                        direca_disparo = 4;
                    }
                }
                /*Verifica o numero de droids atingidos na diagonal       
                (nordeste-sudoeste) para baixo*/
                for(k = i + 1, l = j - 1; (k < linhas) && (l >= 0); k++, l--)
                {
                    if(campo_batalha[k][l] == 1)
                    {
                        droids++;
                        direca_disparo = 4;
                    }
                }
                if(direca_disparo == 4)
                {
                    disparos++;
                }
            }
           
            if(droids > droids_total)
            {
                droids_total = droids;
                pos_lin = i;
                pos_col = j;
                disparos_totais = disparos;
            }
            else if(droids == droids_total)
            {
                /*Caso o maior numero de droids atingidos seja igual em duas 
                posicoes, verifica o que utilizou o menor numero de disparos*/
                if(disparos < disparos_totais)
                {
                    pos_lin = i;
                    pos_col = j;
                    disparos_totais = disparos;
                }
            }
            droids = 0;
            direca_disparo = 0;
        }    
    }
    
    printf("Posicao = (%d,%d)\n", pos_lin, pos_col);
    printf("Droids = %d\n", droids_total);
    printf("Disparos = %d\n", disparos_totais);
 
    return 0;
}
    