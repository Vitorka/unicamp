/*Nome: Vitor Kaoru Aoki
RA: 178474
*/

#include <stdio.h>

/*O programa executa o jogo Cargo-Bot. A partir de uma posicao pre-definida 
para a posicao das caixas, da sequencia em que os programas sao executados e 
dos comandos que cada programa ira executar, ele realiza o rearranjo da posicao 
das caixas. Em suas regras, fica definido um conjunto de condicoes, que se 
utilizadas, definem se os comandos seguidos a elas, irao ou nao ser executados*/
int main()
{
    int i, j, k, l, m, posicoes, max_caixas, num_exec, num_prog, num_comand, 
    condicao, acidente = 0;
    int /*n, o,*/ p;
    char caixas[10][10], execucoes[60], comando[9][60], braco = '0';
    
    scanf("%d %d %d %d %d", &posicoes, &max_caixas, &num_prog, &num_comand, 
    &num_exec);
    
    /*Le a posicao das caixas*/
    scanf(" ");
    for(i = 0; i < max_caixas; i++) 
    {
        scanf("%s", caixas[i]);
    }
    
    /*Le a ordem de execucao dos programas*/
    scanf(" ");
    scanf("%s", execucoes);
    
    /*Le os comandos que cada programa ira executar*/
    scanf(" ");
    for(j = 1; j <= num_prog; j++)
    {
        scanf("%s", comando[j]);
    }
    
    /*Executa os programas na ordem deifinida*/
    for(k = 0, m = 0, p = 1; (k < num_exec) && (acidente == 0); k++)
    {
        /*Variavel utilizada para definir na matriz de comandos, qual programa 
        sera executado*/
        j = execucoes[k] - '0';
        
        /*Executa cada comando do programa escolhido*/
        for(l = 0; (comando[j][l] != '*') && (acidente == 0); l++, i = 0, p++)
        {
            condicao = 0;
            printf("%c\n", comando[j][l]);
            /*Condicionais que definem se o comando seguinte a alguma delas 
            sera ou nao executado, de acordo com a cor da caixa que o braco 
            esta segurando ou se ele esta segurando alguma caixa*/
            if((comando[j][l] == 'B') && (braco == 'B'))
            {
                condicao = 1;
                l++;
            }
            else if((comando[j][l] == 'G') && (braco == 'G'))
            {
                condicao = 1;
                l++;
            }
            else if((comando[j][l] == 'Y') && (braco == 'Y'))
            {
                condicao = 1;
                l++;
            }
            else if((comando[j][l] == 'A') && (braco != '0'))
            {
                printf("%d\n", l);
                condicao = 1;
                l++;
            }
            else if((comando[j][l] == 'N') && (braco == '0'))
            {
                condicao = 1;
                l++;
            }
            else if((comando[j][l] == 'L') || (comando[j][l] == 'R') || 
                (comando[j][l] == 'D'))
            {
                condicao = 1;
            }
            
            /*Executa o comando do braco*/
            if(condicao == 1)
            {
                /*Executa o comando para o braco se mover para a esquerda*/
                if((comando[j][l] == 'L') && (m != 0))
                {
                    /*Identifica se houve um acidente*/
                    if((caixas[0][m - 1] != '.') && (braco != '0'))
                    {
                        acidente = 1;
                    }
                    else
                    {
                        m--;
                    }
                }
                /*Executa o comando do braco para a direita*/
                else if((comando[j][l] == 'R') && (m != posicoes - 1))
                {
                    /*Identifica se houve um acidente*/
                    if((caixas[0][m + 1] != '.') && (braco != '0'))
                    {
                        acidente = 1;
                    }
                    else
                    {
                        m++;
                    }
                }
                /*Executa o movimento de descida do braco*/
                else if(comando[j][l] == 'D')
                {
                    /*Caso o braco nao esteja segurando nenhuma caixa, pega uma 
                    caixa, se houver, existente na posicao*/
                    if(braco == '0')
                    {  
                        for(i = 0; (i < max_caixas) && (braco == '0'); i++)
                        {
                            if(caixas[i][m] != '.')
                            {
                                braco = caixas[i][m];
                                caixas[i][m] = '.';
                            }
                        }
                    }
                    /*Caso ele esteja segurando uma caixa, deposita-a na 
                    posicao onde ele se encontra*/
                    else
                    {
                        for(i = 0; (i < max_caixas) && (braco != '0'); i++)
                        {
                            if(caixas[i][m] != '.')
                            {
                                caixas[i - 1][m] = braco;
                                braco = '0';
                            }
                            else if(i == max_caixas - 1)
                            {
                                caixas[i][m] = braco;
                                braco = '0';
                            }
                        }
                    }
                }
            }
            /*Caso nenhuma das condicionais seja verdadeira, nao executa o 
            comando seguinte a ela*/
            else
            {
                l++;
            }
            
            /*printf("%d\n", p);
            for(n = 0; n < max_caixas; n++)
            {
                for(o = 0; o < posicoes; o++)
                {
                    printf("%c", caixas[n][o]);
                }
                printf("\n");
            }
            printf("\n");*/
        }
    }
    
    if(acidente == 1)
    {
        printf("Um acidente ocorreu\n");
    }
    else
    {
        for(i = 0; i < max_caixas; i++, printf("\n")) 
        {    
            printf("%s", caixas[i]);
        }
    }
    
    return 0;
}

