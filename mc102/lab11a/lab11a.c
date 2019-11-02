/*Nome: Vitor Kaoru Aoki   
  RA: 178474
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 10

typedef struct
{
    int num_conta;
    int num_agencia;
    char nome[22];
    char sobrenome[22];
    double saldo;
} contas;

typedef struct
{
    int origem_conta;
    int origem_agencia;
    double valor;
    int destino_conta;
    int destino_agencia;
} transferencias;
    
/*O programa tem como finalidade verificar se as transferencias bancarias 
realizadas em um dia, sao possiveis. Caso sejam possiveis, realiza a 
transferencia de acordo com os dados de origem e de destino*/    
int main(){
    
    int i, j, k, num_cli, num_transf;
    contas bancarias[max];  
    transferencias *dia;
    
    scanf("%d %d", &num_cli, &num_transf);
    
    dia = malloc(num_transf * sizeof(transferencias));
    
    /*Le os dados bancarios dos clientes*/
    for(i = 0; i < num_cli; i++)
    {
        scanf("%d", &bancarias[i].num_conta); 
        scanf("@");
        scanf("%d",&bancarias[i].num_agencia);
        
        scanf(" ");
        scanf("%s", bancarias[i].nome);
        
        scanf(" ");
        scanf("%s", bancarias[i].sobrenome);
        
        scanf("%lf", &bancarias[i].saldo);
    }
    
    /*Le as possiveis transferencias bancarias do dia*/
    scanf(" ");
    for(i = 0; i < num_transf; i++)
    {
        scanf("%d", &dia[i].origem_conta); 
        scanf("@");
        scanf("%d", &dia[i].origem_agencia);
        
        scanf(" >> ");
        scanf("%lf", &dia[i].valor);
        
        scanf(" >> ");
        scanf("%d", &dia[i].destino_conta); 
        scanf("@");
        scanf("%d", &dia[i].destino_agencia);   
    }
    
    /*Verifica se as transferencias sao possiveis*/
    for(i = 0; i < num_transf; i++)
    {
        for(j = 0; j < num_cli; j++)
        {   
            /*Verifica se o numero da conta e o numero da agencia de origem, 
            sao verdadeiros*/
            if((bancarias[j].num_conta == dia[i].origem_conta) && 
               (bancarias[j].num_agencia == dia[i].origem_agencia) && 
               (bancarias[j].saldo >= dia[i].valor))
            {
                for(k = 0; k < num_cli; k++)
                {   
                    /*Verifica se o numero da conta e o numero da agencia de 
                    destino, sao verdadeiros*/
                    if((bancarias[k].num_conta == dia[i].destino_conta) && 
                       (bancarias[k].num_agencia == dia[i].destino_agencia))
                    {
                        bancarias[j].saldo -= dia[i].valor;
                        bancarias[k].saldo += dia[i].valor;
                    }
                }
            }
        }
    }
                    
   
    for(i = 0; i < num_cli; i++)
    {
        printf("%d@%d %s %s %.2f\n", bancarias[i].num_conta, 
        bancarias[i].num_agencia, bancarias[i].nome, 
        bancarias[i].sobrenome, bancarias[i].saldo);
    }
    
    free(dia);
 
    return 0;
}
    