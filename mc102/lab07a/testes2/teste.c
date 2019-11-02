/*Nome: Vitor Kaoru Aoki
 *  RA: 178474
 */

#include <stdio.h>

int main()
{
    int i, j, posicoes, max_caixas, num_exec, num_prog, num_comand;
    char caixas[10][10], execucoes[60], comando[9][60];
    
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
    
    printf("\n");
    
    /*Imprimi os primeiros numeros inteiros*/
    printf("%d %d %d %d %d\n", posicoes, max_caixas, num_prog, num_comand, 
    num_exec);
    
    /*Imprimi a posicao das caixas*/
    for(i = 0; i < max_caixas; i++, printf("\n")) 
    {    
        printf("%s", caixas[i]);
    }
    
    /*Imprimi a ordem da execucao dos programas*/
    printf("%s\n", execucoes);
    
    /*Imprimi os programas a serem executados*/
    for(j = 1; j <= num_prog; j++, printf("\n"))
    {
        printf("%s", comando[j]);
    }
    
    return 0;
}

