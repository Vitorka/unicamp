#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char ra[7];
    char nome[21];
    char comando[10];
    char letras_nome;
    int i = 0;
    int flag = 0;
    int flag2 = 0;
    
    while(flag2 == 0)
    {
        flag = 0;
        
        scanf(" ");
        scanf("%s", comando);
        
        /*Caso seja um comando de inserir*/
        if(comando[1] == 'n')
        {
            scanf(" ");
            scanf("%s", ra);
            
            scanf(" ");
            scanf("%c", &letras_nome);
            while(flag == 0)
            {
                scanf("%c", &letras_nome);
                
                if(letras_nome != '"')
                {
                    nome[i] = letras_nome;
                }
                else
                {
                    flag = 1;
                }
                i++;    
            }
            printf("%s ", ra);
            printf("%s\n", nome);    
        }
        /*Caso seja um comando de imprimir*/
        else if(comando[1] == 'm')
        {
        }
        /*Caso seja um comando de consulta*/
        else if(comando[0] == 'c')
        {
        }
        /*Caso seja um comando de remover*/
        else if(comando[0] == 'r')
        {   
        }
        /*Caso termine o programa*/
        else if(comando[0] == 's')
        {
            flag2 = 1;
        }      
    }
    
    return 0;
}
    