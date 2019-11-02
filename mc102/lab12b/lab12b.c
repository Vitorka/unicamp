/* Laboratorio 12b - Bola de Ouro
 *   Autor: Vitor Kaoru Aoki
 *   RA: 178474   
 *   Email: Seu e-mail aqui
 */

#include <stdio.h>
#include <string.h>

/* Tamanho maximo do nome do jogador */
#define MAXNOME 26
/* Tamanho maximo do nome dos arquivos de entrada/saida */
#define MAXNOMEARQ 101
/* Numero maximo de jogadores */
#define MAXJOGADORES 40

/* Jogador:
 * nome = nome do jogador
 * C1 = numero de gols
 * C2 = numero de assistencias
 * C3 = numero de dribles feitos
 * C4 = numero de gols contra
 * C5 = numero de cartoes vermelhos
 * C6 = numero de cartoes amarelos
 */
struct Jogador {
    char nome[MAXNOME];
    int C1;
    int C2;
    int C3;
    int C4;
    int C5;
    int C6;
};

typedef struct Jogador Jogador;

int main(int argc, char **argv) {
    /* Nome do arquivo binario com as estatisticas */
    char nomeArqEstat[MAXNOMEARQ];
    /* Nome do arquivo binario de saida */
    char nomeArqSaida[MAXNOMEARQ];
    
    int i, j, k;
    int num_jog, num_jog_rod, rodadas, notas[MAXJOGADORES], flag = 0;
    int pesos[6], estatisticas, aux3;
    char aux[MAXNOME];
    FILE *arqin, *arqout;
    Jogador estat_jog[MAXJOGADORES], aux2;
    
    /* Lendo os nomes dos arquivos binarios */
    strcpy(nomeArqEstat, argv[1]);
    strcpy(nomeArqSaida, argv[2]);   
    
    arqin = fopen(nomeArqEstat, "rb");
    arqout = fopen(nomeArqSaida, "wb");
    
    /*Le o numero de jogadores e armazena os scouts de cada jogador a partir do 
    arquivo binario de entrada*/ 
    fread(&num_jog, sizeof(int), 1, arqin);
    fread(estat_jog, sizeof(Jogador), num_jog, arqin);
    
    /*Le os pesos de cada estatistica do arquivo de entrada padrao*/
    for(i = 0; i < 6; i++)
    {
        scanf("%d", &pesos[i]);    
    }
    
    /*Le o numero de rodadas do arquivo padrao*/
    scanf("%d", &rodadas);
    
    for(i = 0; i < rodadas; i++)
    {
        /*Le o numero de jogadores de cada rodada a partir da entrada padrao*/
        scanf(" ");
        scanf("%d", &num_jog_rod);
        
        /*Le o nome dos jogadores de cada rodada e suas respectivas 
        estatisticas na rodada*/
        for(j = 0; j < num_jog_rod; j++)
        {
            flag = 0;
            scanf(" ");
            scanf("%s", aux);
            
            for(k = 0; flag == 0; k++)
            {
                /*Verifica se o jogador lido esta no scout de entrada, e caso 
                esteja atualiza suas estatisticas*/
                if(strcmp(estat_jog[k].nome, aux) == 0)
                {
                    scanf(" ");
                
                    scanf("%d", &estatisticas);
                    estat_jog[k].C1 += estatisticas;
                    scanf(" ");
                    
                    scanf("%d", &estatisticas);
                    estat_jog[k].C2 += estatisticas;
                    scanf(" ");
                    
                    scanf("%d", &estatisticas);
                    estat_jog[k].C3 += estatisticas;
                    scanf(" ");
                    
                    scanf("%d", &estatisticas);
                    estat_jog[k].C4 += estatisticas;
                    scanf(" ");
                    
                    scanf("%d", &estatisticas);
                    estat_jog[k].C5 += estatisticas;
                    scanf(" ");
                    
                    scanf("%d", &estatisticas);
                    estat_jog[k].C6 += estatisticas;
                
                    flag = 1;
                }
            }
        }
    }
    
    /*Armazena no arquivo binario de saida o numero de jogadores iniciais e 
    seus respectivos scouts atualizados*/
    fwrite(&num_jog, sizeof(int), 1, arqout);
    fwrite(estat_jog, sizeof(Jogador), num_jog, arqout);
    
    for(i = 0; i < num_jog; i++)
    {
        notas[i] = 0;
    }
    
    /*Calcula as notas de cada jogador armazenado, com os respectivos pesos de 
    cada estatistica*/ 
    for(i = 0; i < num_jog; i++)
    {
        notas[i] += (estat_jog[i].C1 * pesos[0]);
        notas[i] += (estat_jog[i].C2 * pesos[1]);
        notas[i] += (estat_jog[i].C3 * pesos[2]);
        notas[i] -= (estat_jog[i].C4 * pesos[3]);
        notas[i] -= (estat_jog[i].C5 * pesos[4]);
        notas[i] -= (estat_jog[i].C6 * pesos[5]);
    }
    
    /*Ordena os jogadores de forma decrescente de acordo com suas notas*/
    for(i = 0; i < num_jog; i++)
    {   
        k = i;
        for(j = i + 1; j < num_jog; j++)
        {
            if(notas[k] < notas[j])
            {
                k = j;
            }
        }
        /*Ordena o vetor de notas*/
        aux3 = notas[i];
        notas[i] = notas[k];
        notas[k] = aux3;  
        
        /*Ordena os jogadores*/
        aux2 = estat_jog[i];
        estat_jog[i] = estat_jog[k];
        estat_jog[k] = aux2; 
    }
    
    /*Caso a pontuacao seja igual, ordena pela ordem lexicografica*/
    for(i = 0; i < num_jog; i++)
    {
        flag = 0;
        
        for(j = i + 1; (j < num_jog) && (flag == 0); j++)
        {
            if(notas[i] == notas[j])
            {
                if(strcmp(estat_jog[i].nome, estat_jog[j].nome) > 0)
                {
                    aux2 = estat_jog[i];
                    estat_jog[i] = estat_jog[j];
                    estat_jog[j] = aux2;
                }
            }
            else
            {
                flag = 1;
            }
        }
    }
            
    
    for(i = 0; i < 3; i++)
    {
        printf("%s\n", estat_jog[i].nome);
    }
    
    fclose(arqin);
    fclose(arqout);

    return 0;
}
