/*Nome: Vitor Kaoru Aoki
 RA: 178474*/

#include <stdio.h>

int movimentos(char comando[9][60], char caixas[10][10], char *braco,
               int *posicao, int j, int k, int max_caixas, int posicoes)
{
    int i;
    
    /*Executa o comando para o braco se mover para a esquerda*/
    if((comando[j][k] == 'L') && (*posicao != 0))
    {
        /*Identifica se houve um acidente*/
        if((caixas[0][(*posicao) - 1] != '.') && (*braco != '0'))
        {
            return 1;
        }
        else
        {
            (*posicao)--;
            return 0;
        }
    }
    /*Executa o comando do braco para a direita*/
    else if((comando[j][k] == 'R') && (*posicao != posicoes - 1))
    {
        /*Identifica se houve um acidente*/
        if((caixas[0][(*posicao) + 1] != '.') && (*braco != '0'))
        {
            return 1;
        }
        else
        {
            (*posicao)++;
            return 0;
        }
    }
    /*Executa o movimento de descida do braco*/
    else if(comando[j][k] == 'D')
    {
        /*Caso o braco nao esteja segurando nenhuma caixa, pega uma 
        caixa, se houver, existente na posicao*/
        if(*braco == '0')
        {  
            for(i = 0; (i < max_caixas) && (*braco == '0'); i++)
            {
                if(caixas[i][(*posicao)] != '.')
                {
                    *braco = caixas[i][(*posicao)];
                    caixas[i][(*posicao)] = '.';
                    return 0;
                }
            }
        }
        /*Caso ele esteja segurando uma caixa, deposita-a na posicao onde 
        ele se encontra*/
        else
        {
            for(i = 0; (i < max_caixas) && (*braco != '0'); i++)
            {
                if(caixas[i][(*posicao)] != '.')
                {
                    caixas[i - 1][(*posicao)] = *braco;
                    *braco = '0';
                    return 0;
                }
                else if(i == max_caixas - 1)
                {
                    caixas[i][(*posicao)] = *braco;
                    *braco = '0';
                    return 0;
                }
            }
        }
    }
    return 0;
}


int condicao(char comando[9][60], char caixas[10][10], char *braco,
             int *num_exec, int max_caixas, int posicoes, int *posicao, 
             int j)
{
    int k = 0, acidente = 0, aux;
    int flag = 0;
    
    (*num_exec)--;
    
    /*Executa cada comando do programa escolhido*/
    for(k = 0; (comando[j][k] != '*') && (acidente == 0); k++, flag = 0)
    {   
        /*Condicionais que definem se o comando seguinte a alguma delas 
        sera ou nao executado, de acordo com a cor da caixa que o braco 
        esta segurando ou se ele esta segurando alguma caixa*/
        if((comando[j][k] == 'B') && (*braco == 'B'))
        {
            k++;
            flag = 1;
        }
        else if((comando[j][k] == 'G') && (*braco == 'G'))
        {
            k++;
            flag = 1;
        }
        else if((comando[j][k] == 'Y') && (*braco == 'Y'))
        {
            k++;
            flag = 1;
        }
        else if((comando[j][k] == 'A') && (*braco != '0'))
        {
            k++;
            flag = 1;
        }
        else if((comando[j][k] == 'N') && (*braco == '0'))
        {
            k++;
            flag = 1;
        }
        else if((comando[j][k] == 'L') || (comando[j][k] == 'R') || 
            (comando[j][k] == 'D'))
        {
            flag = 1;
        }
        else if((comando[j][k] >= '1') && (comando[j][k] <= '9'))
        {
            if((*num_exec) != 0)
            {
                aux = comando[j][k] - '0';
                acidente = condicao(comando, caixas, braco, num_exec, 
                                    max_caixas, posicoes, posicao, aux);
            }
        }
        /*Caso nenhuma das condicionais seja verdadeira, nao executa o 
        comando seguinte a ela*/
        else
        {
            k++;
        }
        
        /*Caso a condicao seja verdadeira executa o comando*/
        if(flag == 1)
        {
            /*Verifica se o comando eh uma chamada para executar uma outra 
            linha de comando*/
            if((comando[j][k] >= '1') && (comando[j][k] <= '9'))
            {
                if((*num_exec) != 0)
                {
                    aux = comando[j][k] - '0';
                    acidente = condicao(comando, caixas, braco, num_exec, 
                                        max_caixas, posicoes, posicao, aux);
                }
            }
            else
            {   
                acidente = movimentos(comando, caixas, braco, posicao, j, k, 
                                      max_caixas, posicoes);
            }
        }
    }
    
    /*Nao ocorreu um acidente*/
    if(acidente == 0)
    {
        return 0;
    }
    /*Ocorreu um acidente*/
    else 
    {
        return 1;
    }
}


/*O programa executa o jogo Cargo-Bot. A partir de uma posicao pre-definida 
para a posicao das caixas e dos comandos que cada programa ira executar, ele 
realiza o rearranjo da posicao das caixas. Em suas regras, fica definido um 
conjunto de condicoes, que se utilizadas, definem se os comandos seguidos a 
elas, irao ou nao ser executados*/
int main()
{
    int i, j, posicoes, max_caixas, num_exec, num_prog, num_comand; 
    int acidente = 0, posicao = 0;
    char caixas[10][10], comando[10][60], braco = '0';
    
    scanf("%d %d %d %d %d", &posicoes, &max_caixas, &num_prog, &num_comand, 
          &num_exec);
    
    /*Le a posicao das caixas*/
    for(i = 0; i < max_caixas; i++) 
    {
        scanf(" ");
        for(j = 0; j < posicoes; j++)
        {
            scanf("%c", &caixas[i][j]);
        }
    }
    
    /*Le os comandos que cada programa ira executar*/
    for(i = 1; i <= num_prog; i++)
    {
        scanf(" ");
        scanf("%s", comando[i]);
    }
    
    /*Chama a funcao que executa os comandos*/
    acidente = condicao(comando, caixas, &braco, &num_exec, max_caixas, 
                        posicoes, &posicao, 1);
    
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

