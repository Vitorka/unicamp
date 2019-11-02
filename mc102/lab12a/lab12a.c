/* Laboratorio 12a - Tweet Extractor
 *   Autor: Vitor Kaoru Aoki
 *   RA: 178474
 *   Email: 
 */

#include <stdio.h>
#include <string.h>

#define MAX_FILENAME 25
#define MAX_ENTITY 10

/* Funcao que converte uma entidade no caractere correspondente,
 *   supondo que o caractere '&' foi previamente lido no arquivo de
 *   entrada (arqin). Se a entidade eh diferente de aspas simples ou
 *   aspas dupla, a funcao simplesmente o ignora, caso contrario ela
 *   imprime o caractere correspondente no arquivo de saida (arqout). */
void converte_entidade(FILE *arqin, FILE *arqout) {
    char c, entidade[MAX_ENTITY];
    int i = 0;
    
    /* armazena o codigo da entidade ate encontrar o caractere ';' */
    c = fgetc(arqin);
    while (c != ';') {
        entidade[i++] = c;
        c = fgetc(arqin);
    }
    entidade[i] = '\0';
    
    /* se a entidade corresponde ao caractere aspas simples ou aspas duplas,
     *       imprime o caractere no arquivo de saida */
    if (!strcmp(entidade, "#39"))
        fprintf(arqout, "\'");
    else if(!strcmp(entidade, "quot"))
        fprintf(arqout, "\"");
}

void extrai_tweets(char nomearqin[], char nomearqout[]) {
    
    FILE *arqin, *arqout;
    char aux, aux2[38], caract;
    int i, flag, flag2, verificador;
    
    arqin = fopen(nomearqin, "r");
    arqout = fopen(nomearqout, "w");
    
    /*Le o arquivo ate que o fscanf retorne EOF, indicando o fim do arquivo*/ 
    while(fscanf(arqin, "%c", &aux) != EOF)
    {
        flag = 0;
        flag2 = 0;
        verificador = 1;
        
        /*Se encontrar o caractere '<', verifica e ele faz parte de uma flag 
        valida para que seja adicionada ao arquivo de saida*/
        if(aux == '<')
        {
            fscanf(arqin, "%c", &aux);
            
            /*Caso encontre um 'p', le ate encontrar a class da flag*/
            if(aux == 'p')
            {
                fscanf(arqin, "%c", &aux);
                
                while(aux != '>')
                {
                    fscanf(arqin, "%c", &aux);
                    
                    if((aux == '\"') && (flag2 == 0))
                    {
                        fscanf(arqin, "%c", &caract);
                        
                        /*Apos encontrar a class, verifica se eh a class valida 
                        do tweet*/
                        for(i = 0; (caract != '\"') && (i < 38); i++)
                        {
                            aux2[i] = caract;
                            fscanf(arqin, "%c", &caract);
                        }
                        aux2[i] = '\0';
                        
                        verificador = strcmp
                        (aux2, "ProfileTweet-text js-tweet-text u-dir");
                        
                        if(verificador == 0)
                        {
                            flag2 = 1;
                        }
                    }   
                }
                
                /*Caso seja uma class valida, armazena no arquivo de saida, 
                todo o tweet*/
                while((flag == 0) && (verificador == 0))
                {
                    fscanf(arqin, "%c", &aux);
                    
                    /*Caso encontre um caractere '<', verifica se eh uma flag 
                    de termino do twiter ou uma flag de formatacao do tweet*/ 
                    if(aux == '<')
                    {
                        fscanf(arqin, "%c", &aux);
                        
                        /*Caso seja um caractere '/', verifica se o proximo 
                        caractere eh um 'p', indicando uma flag de fim do 
                        tweet*/
                        if(aux == '/')
                        {
                            fscanf(arqin, "%c", &aux);
                            
                            if(aux == 'p')
                            {
                                flag = 1;
                                fscanf(arqin, "%c", &aux);
                                aux = '\n';
                                fprintf(arqout, "%c", aux);
                            }
                            /*Caso nao seja um caractere 'p', representando o 
                            fim do tweet, le os caracteres restantes ate o 
                            caractere '>', indicando o fim da flag*/
                            else
                            {
                                while(aux != '>')
                                {
                                    fscanf(arqin, "%c", &aux);
                                }
                            }
                        }
                        /*Caso nao seja uma flag indicando o fim do tweet, le 
                        ate encontrar o caractere '>', indicando o fim da flag*/
                        else
                        {
                            while(aux != '>')
                            {
                                fscanf(arqin, "%c", &aux);
                            }
                        }
                    }
                    /*Se encontrar o caractere '&', converte esse caractere 
                    para aspas simples, ou aspas duplas de acordo com as 
                    especificacoes*/
                    else if(aux == '&')
                    {
                        converte_entidade(arqin, arqout);
                    }
                    else
                    {
                        fprintf(arqout, "%c", aux);
                    }
                }
            }
        }
    }   
    fclose(arqin);
    fclose(arqout);
}


int main(int argc, char *argv[]) {  
    char nomearqin[MAX_FILENAME], nomearqout[MAX_FILENAME];
    
    /* Copia os nomes do arquivo de entrada e de saida nas variaveis */
    strcpy(nomearqin, argv[1]);
    strcpy(nomearqout, argv[2]);
    
    extrai_tweets(nomearqin, nomearqout);
    
    return 0;
}
