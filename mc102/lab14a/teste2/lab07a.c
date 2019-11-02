/*Nome: Vitor Kaoru Aoki
 * RA: 178474
 */

#include <stdio.h>



int movimentos(char comando[9][60], char caixas[10][10], char braco[],
               int pos_braco[], int j, int k, int max_caixas, int posicoes)
{
    int i;
    
    /*Executa o comando para o braco se mover para a esquerda*/
    if((comando[j][k] == 'L') && (pos_braco[0] != 0))
    {
        /*Identifica se houve um acidente*/
        if((caixas[0][pos_braco[0] - 1] != '.') && (braco[0] != '0'))
        {
            return 1;
        }
        else
        {
            pos_braco[0]--;
            return 0;
        }
    }
    /*Executa o comando do braco para a direita*/
    else if((comando[j][k] == 'R') && (pos_braco[0] != posicoes - 1))
    {
        /*Identifica se houve um acidente*/
        if((caixas[0][pos_braco[0] + 1] != '.') && (braco[0] != '0'))
        {
            return 1;
        }
        else
        {
            pos_braco[0]++;
            return 0;
        }
    }
    /*Executa o movimento de descida do braco*/
    else if(comando[j][k] == 'D')
    {
        /*Caso o braco nao esteja segurando nenhuma caixa, pega uma 
        caixa, se houver, existente na posicao*/
        if(braco[0] == '0')
        {  
            for(i = 0; (i < max_caixas) && (braco[0] == '0'); i++)
            {
                if(caixas[i][pos_braco[0]] != '.')
                {
                    braco[0] = caixas[i][pos_braco[0]];
                    caixas[i][pos_braco[0]] = '.';
                    return 0;
                }
            }
        }
        /*Caso ele esteja segurando uma caixa, deposita-a na posicao onde 
        ele se encontra*/
        else
        {
            for(i = 0; (i < max_caixas) && (braco[0] != '0'); i++)
            {
                if(caixas[i][pos_braco[0]] != '.')
                {
                    caixas[i - 1][pos_braco[0]] = braco[0];
                    braco[0] = '0';
                    return 0;
                }
                else if(i == max_caixas - 1)
                {
                    caixas[i][pos_braco[0]] = braco[0];
                    braco[0] = '0';
                    return 0;
                }
            }
        }
    }
    return 0;
}


int condicao(char comando[9][60], char caixas[10][10], char execucoes[], 
             char braco[],
             int num_exec, int max_caixas, int posicoes, int pos_braco[])
{
    int i, j, k = 0, acidente = 0;
    
    /*Executa os programas na ordem deifinida*/
    for(i = 0; (i < num_exec) && (acidente == 0); i++)
    {
        /*Variavel utilizada para definir na matriz de comandos, qual programa 
        sera executado*/
        j = execucoes[i] - '0';
        
        /*Executa cada comando do programa escolhido*/
        for(k = 0; (comando[j][k] != '*') && (acidente == 0); k++)
        {   
            
            /*Condicionais que definem se o comando seguinte a alguma delas 
            sera ou nao executado, de acordo com a cor da caixa que o braco 
            esta segurando ou se ele esta segurando alguma caixa*/
            if((comando[j][k] == 'B') && (braco[0] == 'B'))
            {
                k++;
                acidente = movimentos(comando, caixas, braco, pos_braco, j, k, 
                                      max_caixas, posicoes);
            }
            else if((comando[j][k] == 'G') && (braco[0] == 'G'))
            {
                k++;
                acidente = movimentos(comando, caixas, braco, pos_braco, j, k, 
                                      max_caixas, posicoes);
            }
            else if((comando[j][k] == 'Y') && (braco[0] == 'Y'))
            {
                k++;
                acidente = movimentos(comando, caixas, braco, pos_braco, j, k, 
                                      max_caixas, posicoes);
            }
            else if((comando[j][k] == 'A') && (braco[0] != '0'))
            {
                k++;
                acidente = movimentos(comando, caixas, braco, pos_braco, j, k, 
                                      max_caixas, posicoes);
            }
            else if((comando[j][k] == 'N') && (braco[0] == '0'))
            {
                k++;
                acidente = movimentos(comando, caixas, braco, pos_braco, j, k, 
                                      max_caixas, posicoes);
            }
            else if((comando[j][k] == 'L') || (comando[j][k] == 'R') || 
                    (comando[j][k] == 'D'))
            {
                acidente = movimentos(comando, caixas, braco, pos_braco, j, k, 
                                      max_caixas, posicoes);
            }
            /*Caso nenhuma das condicionais seja verdadeira, nao executa o 
            comando seguinte a ela*/
            else
            {
                k++;
            }
        }
    }
    
    if(acidente == 0) /*Nao ocorreu um acidente*/
    {
        return 0;
    }
    else /*Ocorreu um acidente*/
    {
        return 1;
    }
}


/*O programa executa o jogo Cargo-Bot. A partir de uma posicao pre-definida 
para a posicao das caixas, da sequencia em que os programas sao executados e 
dos comandos que cada programa ira executar, ele realiza o rearranjo da posicao 
das caixas. Em suas regras, fica definido um conjunto de condicoes, que se 
utilizadas, definem se os comandos seguidos a elas, irao ou nao ser 
executados*/
int main()
{
    int i, j, posicoes, max_caixas, num_exec, num_prog, num_comand; 
    int acidente = 0, pos_braco[1];
    char caixas[10][10], execucoes[60], comando[10][60], braco[1];
    
    scanf("%d %d %d %d %d", &posicoes, &max_caixas, &num_prog, &num_comand, 
          &num_exec);
    
    /*Le a posicao das caixas*/
    scanf(" "); 
    for(i = 0; i < max_caixas; i++) 
    {
        scanf(" ");
        for(j = 0; j < posicoes; j++)
        {
            scanf("%c", &caixas[i][j]);
        }
    }
    
    /*Le a ordem de execucao dos programas*/
    scanf(" ");
    scanf("%s", execucoes);
    
    /*Le os comandos que cada programa ira executar*/
    
    for(i = 1; i <= num_prog; i++)
    {
        scanf(" ");
       scanf("%s", comando[i]); 
    }
    
    pos_braco[0] = 0;
    braco[0] = '0';
    acidente = condicao(comando, caixas, execucoes, braco, num_exec, 
                        max_caixas, posicoes, pos_braco);
    
    if(acidente == 1)
    {
        printf("Um acidente ocorreu\n");
    }
    else
    {
        for(i = 0; i < max_caixas; i++) 
        {    
            for(j = 0; j < posicoes; j++)
            {
                printf("%c", caixas[i][j]);
            }
            printf("\n");
        }
    }
    
    return 0;
}

