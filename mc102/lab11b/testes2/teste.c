#include <stdio.h>
#include <string.h>

struct time {
    char nome[21];
    int indice, pontos, vitorias;
    int pontosGanhos, pontosPerdidos, setsGanhos, setsPerdidos; 
};
typedef struct time time_t;

void procura_nomes(time_t *times, int *ocupado, int *j);

int main()
{
    int i = 0, j, k, l = 0, flag2 = 0, pontos1 = 0, pontos2 = 0;
    int sets1 = 0, sets2 = 0, ocupado[6];
    time_t times[6];
    
    for(i = 0; i < 6; i++)
    {
        times[i].pontos = 0;
        times[i].setsGanhos = 0;
        times[i].setsPerdidos = 0;
        times[i].vitorias = 0;
        times[i].pontosGanhos = 0;
        times[i].pontosPerdidos = 0;
    }
    
    for(i = 0; i < 6; i++)
    {
        ocupado[i] = 0;
    }
   
    
    for(l = 0; l < 15; l++)
    {   
        /*Le os nomes dos paises*/
        /*for(i = 0; (i < 6) && (flag == 0); i++)
    scanf(" ");
    scanf("%s", aux);
        {   
            if((strcmp(aux, times[i].nome) != 0) 
               && (ocupado[i] == 0))  
            {
                strcpy(times[i].nome, aux);
                j = i;
                flag = 1;
                ocupado[i] = 1;
            }
            else if(strcmp(aux, times[i].nome) == 0)
            {
                j = i;
                flag = 1;
                ocupado[i] = 1;
            }
        }*/
        
        /*Le os nomes dos paises*/
        /*for(i = 0; (i < 6) && (flag == 0); i++)
        {
        flag = 0;
        scanf(" ");
        scanf("%s", aux);
            if((strcmp(aux, times[i].nome) != 0) 
               && (ocupado[i] == 0))            
            {
                strcpy(times[i].nome, aux);
                k = i;
                flag = 1;
                ocupado[i] = 1;
            }
            else if(strcmp(aux, times[i].nome) == 0)
            {
                k = i;
                flag = 1;
                ocupado[i] = 1;
            }
        }*/
        
        procura_nomes(times, ocupado, &j);
        procura_nomes(times, ocupado, &k);
        
        scanf(" ");
        for(i = 0; flag2 == 0; i++)
        {
            scanf("%d", &pontos1);
            times[j].pontosGanhos += pontos1;
            times[k].pontosPerdidos += pontos1;
            
            scanf("-");
            scanf("%d", &pontos2);
            times[k].pontosGanhos += pontos2;
            times[j].pontosPerdidos += pontos2;
            
            if(pontos1 > pontos2)
            {
                times[j].setsGanhos++;
                times[k].setsPerdidos++;
                sets1++;
            }
            else
            {
                times[k].setsGanhos++;
                times[j].setsPerdidos++;
                sets2++;
            }
           
            if((sets1 == 3) || (sets2 == 3))
            {
                flag2 = 1;
            }
        }
        
        if(sets1 > sets2)
        {
            times[j].vitorias++;
        }
        else
        {
            times[k].vitorias++;
        }
        
        /*flag = 0;*/
        flag2 = 0;
        sets1 = 0;
        sets2 = 0;
    }
    
    for(i = 0; i < 6; i++)
    {
        times[i].pontos = times[i].pontosGanhos - times[i].pontosPerdidos;
    }
    
    printf("\n");
    for(i = 0; i < 6; i++)
    {
        printf("Pais: %s\n", times[i].nome);
        printf("Vitorias: %d\n", times[i].vitorias);
        printf("Sets ganhos: %d\n", times[i].setsGanhos);
        printf("Sets perdidos: %d\n", times[i].setsPerdidos);
        printf("Pontos ganhos: %d\n", times[i].pontosGanhos);
        printf("Pontos perdidos: %d\n", times[i].pontosPerdidos);
        printf("Pontos totais: %d\n", times[i].pontos);
        printf("\n");
    }
    
    return 0;
}

void procura_nomes(time_t *times, int *ocupado, int *j)
{
    int i, flag = 0;
    char aux[21];
    
    scanf(" ");
    scanf("%s", aux);
    
    for(i = 0; (i < 6) && (flag == 0); i++)
    {   
        if((strcmp(aux, times[i].nome) != 0) 
            && (ocupado[i] == 0))  
        {
            strcpy(times[i].nome, aux);
            *j = i;
            flag = 1;
            ocupado[i] = 1;
        }
        else if(strcmp(aux, times[i].nome) == 0)
        {
            *j = i;
            flag = 1;
            ocupado[i] = 1;
        }
    }
}

        



            