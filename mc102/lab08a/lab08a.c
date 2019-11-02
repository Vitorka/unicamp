/*Nome: Vitor Kaoru Aoki
 * RA: 178474
 */

#include <stdio.h>
#include <stdlib.h>

void add(int *n1, int tam_n1, int *n2, int tam_n2, int *result);
void subtract(int *n1, int tam_n1, int *n2, int tam_n2, int *result);
void multiply(int *n1, int tam_n1, int *n2, int tam_n2, int *result);

int main(){
    
    char operacao, digito;
    int tam_n1, tam_n2, *n1, *n2, i, *result;
    
    scanf("%d %d", &tam_n1, &tam_n2);
    scanf(" %c", &operacao);
    
    n1 = malloc(tam_n1 * sizeof(int));
    n2 = malloc(tam_n2 * sizeof(int));
    
    /*Le os numeros que serao utilizados nas operacoes*/
    scanf(" ");
    for(i = tam_n1 - 1; i >= 0; i--)
    {
        scanf("%c", &digito);
        n1[i] = digito - '0';
    }
    scanf(" ");
    for(i = tam_n2 - 1; i >= 0; i--)
    {
        scanf("%c", &digito);
        n2[i] = digito - '0';
    }
    
    /*Condicionais das operacoes*/
    /*Adicao*/
    if(operacao == 'A')
    {
        result = malloc((tam_n1 + 1) * sizeof(int));
        for(i = 0; i < (tam_n1 + 1); i++)
        {
            result[i] = 0;
        }
        add(n1, tam_n1, n2, tam_n2, result);
    }
    /*Subtracao*/
    else if(operacao == 'S')
    {
        result = malloc(tam_n1 * sizeof(int));
        for(i = 0; i < (tam_n1); i++)
        {
            result[i] = 0;
        }
        subtract(n1, tam_n1, n2, tam_n2, result);
    }
    /*Multiplicacao*/
    else if(operacao == 'M')
    {
        result = malloc((tam_n1 + tam_n2) * sizeof(int));
        for(i = 0; i < (tam_n1 + tam_n2); i++)
        {
            result[i] = 0;
        }
        multiply(n1, tam_n1, n2, tam_n2, result);
    }
    
    free(n1);
    free(n2);
    free(result);
    
    return 0;
}

/*Funcao de adicao*/
void add(int *n1, int tam_n1, int *n2, int tam_n2, int *result)
{
    int i, j;
    
    for(i = 0; i < tam_n2; i++)
    {
        /*Verifica se a soma entre os digitos correspondentes eh maior que dez 
        ou nao. Caso seja, adiciona um a casa seguinte*/
        if((n1[i] + n2[i]) >= 10)
        {
            if(i == tam_n1 - 1)
            {
                result[i] = n1[i] + n2[i];    
            }
            else
            {
                result[i] = (n1[i] + n2[i]) % 10;
                n1[i + 1]++;
            }
        }
        else
        {
            result[i] = n1[i] + n2[i];
        }
    }
    
    /*Adiciona ao resultado final, os digitos restantes de n1 que nao foram 
    utilizados na operacao*/ 
    for(j = i; j < tam_n1; j++)
    {    
        if((n1[j] == 10) && (j != tam_n1 - 1))
        {
            result[j] = 0;
            n1[j + 1]++;
        }
        else
        {
            result[j] = n1[j];
        }
    }
    
    for(i = tam_n1 - 1; i >= 0; i--)
    {
        printf("%d", result[i]);
    }
    printf("\n");
}
/*Funcao de subtracao*/
void subtract(int *n1, int tam_n1, int *n2, int tam_n2, int *result)
{
    int i, j, k, flag = 0, contador = 0;
    
    for(i = 0; i < tam_n2; i++, flag = 0)
    {
        if((n1[i] - n2[i]) >= 0)
        {
            result[i] = n1[i] - n2[i];
        }
        else if((n1[i] - n2[i]) < 0)
        {
            /*Caso a subtracao entre os digitos correspondentes de n1 e n2 seja 
            negativa, procura nos digitos seguintes de n1, o primeiro valor 
            diferente de zero, para que possa adicionar aos numeros anteriores, 
            a fim de possibilitar a subtracao de n2 de n1*/
            for(j = (i + 1); (j <= tam_n1) && (flag == 0); j++)
            {
                if(n1[j] != 0)
                {
                    for(k = j; k > i; k--)
                    {
                        if(n1[k] == 0)
                        {
                            n1[k] = 9;
                        }
                        else
                        {
                            n1[k]--;
                        }
                    }
                    n1[i] += 10;
                    flag = 1;
                }
            }
            result[i] = n1[i] - n2[i];
        }
    }
    /*Adiciona ao resultado final, o restante dos digitos de n1 que nao foram 
    utilizados para a operacao*/
    for(j = i; j < tam_n1; j++)
    {    
        result[j] = n1[j];
    }
    /*Verifica se a subtracao dara zero para a impressao de apenas um zero na 
    resposta final*/
    for(i = 0, contador = 0; i < tam_n1; i++)
    {
        if(n1[i] == n2[i])
        {
            contador++;
        }
    }
    if(contador == tam_n1)
    {
        tam_n1 = 1;
    }
    /*Verifica quantos numeros significativos devem aparecer na resposta final*/
    else if(result[tam_n1 - 1] == 0)
    { 
        for(i = 0, contador = 0; i < tam_n1; i++)
        {
            if(result[i] == 0)
            {   
                contador++;
            }
        }
        tam_n1 -= contador;
    } 
    for(i = tam_n1 - 1; i >= 0; i--)
    {
        printf("%d", result[i]);
    }
    printf("\n");   
}
/*Funcao de multiplicacao*/
void multiply(int *n1, int tam_n1, int *n2, int tam_n2, int *result)
{
    int i, j, k, l, m = 0, contador = 0, parada = 0;
    
    /*Identifica se a multiplicacao dara zero*/
    if((tam_n2 == 1) && (n2[0] == 0))
    {
        parada = 1;
    }
    
    /*Caso nao de zero, realiza a operacao de multiplicacao*/
    for(i = 0; (i < tam_n2) && (parada == 0); i++, m++)
    {
        for(j = 0, k = m; j < tam_n1; j++, k++)
        {
            contador++; 
            
            /*Se o resultado da multiplicacao de dois digitos anteriores ao 
            digito que realizara a operacao no momento, der maior ou igual a 
            dez, adiciona a esse digito a parte excedente( maior que nove)*/
            if((result[k - 1] >= 10) && (k != 0))
            {
                result[k] += result[k - 1] / 10;
                result[k - 1] = result[k - 1] % 10;
            }
            /*Se o resultado da multiplicacao dos dois digitos que realizam a 
            operacao, for maior ou igual a dez, e essa operacao nao esta sendo 
            realizada pelos dois ultimos digitos, adiciona ao numero seguinte, 
            o excedente(de nove ate o resultado obtido) da operacao*/ 
            if((n1[j] * n2[i]) >= 10 && (j != tam_n1 - 1))
            {
                result[k] += (n1[j] * n2[i]) % 10;
                result[k + 1] += (n1[j] * n2[i]) / 10;
            }
            else
            {
                result[k] += n1[j] * n2[i];
            }
        }
    }
 
    if(parada == 1)
    {
        printf("%d\n", 0);
    }
    else
    {
        for(l = (tam_n1 + tam_n2) - 2; l >= 0; l--)
        {
            printf("%d", result[l]);
        }
        printf("\n");
    }
}



