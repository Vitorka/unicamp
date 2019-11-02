/*Comandos para o movimento do braco*/
if(comandos[k][p + 1] == 'L')
    {
        if(j != 0)
        {
            j--;
        }
    }
    else if(comandos[k][p + 1] == 'R')
    {
        if(j != posicoes)
        {
            j++;
        }
    }
    else if(comandos[k][p + 1] == 'D')
    {
        if(braco == '0')
        {  
            for(i = 0; (i < max_caixas) && (flag == 0); i++)
            {
                if(caixas[i][j] != '.')
                {
                    braco = caixas[i][j];
                    caixas[i][j] = '.';
                    flag = 1;
                }
            }
        }
        else
        {
            for(i = 0; (i < max_caixas) && (flag == 0); i++)
            {
                if(caixas[i][j] != '.')
                {
                    caixas[i - 1][j] = braco;
                    braco = '0';
                    flag = 1;
                }
            }
        }
    }
    
/*Condicionais da cor das caixas*/
for(m = 0; m < num_exec; m++)
{
    k = execucoes[m] - '0';
    
    for(p = 0; comando[k][p] != '*'; p++)
    {
        /*Condicao para quando a condicional for B*/
        if((comando[k][p] == 'B') && (braco == 'B'))
        {
            funcao_comandos;
            p++;
        }
        /*Condicao para quando a condicional for G*/
        else if((comando[k][p] == 'G') && (braco == 'G'))
        {
            funcao_comandos;
            p++;
        }
        /*Comando para quando a condicional for Y*/
        else if((comando[k][p] == 'Y') && (braco == 'Y'))
        {
            funcao_comandos;
            p++;
        }
        /*Comando para quando a condicional for A*/
        else if((comando[k][p] == 'A') && (braco != '0'))
        {
            funcao_comandos;
            p++;
        }
        /*Comando para quando a condicional for N*/
        else if((comando[k][p] == 'N') && (braco == '0'))
        {
            funcao_comandos;
            p++;
        }
        else if((comando[k][p] == 'L') || (comando[k][p] == 'R') || 
            (comando[k][p] == 'D'))
        {
            funcao_comandos2;
        }
    }
}
        
                
                
                
                
                