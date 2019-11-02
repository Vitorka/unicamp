/* Nome: Vitor Kaoru Aoki
 * RA: 178474
 */

#include <stdio.h>
#include <string.h>

struct time {
    char nome[21];
    int indice, pontos, vitorias;
    int pontosGanhos, pontosPerdidos, setsGanhos, setsPerdidos; 
};
typedef struct time time_t;

/* Atualiza os atributos relativos aos sets e aos pontos */
void atualizaSetsPontos(time_t *time, int setsGanhos, int setsPerdidos, 
                        int pontosGanhos, int pontosPerdidos) {
    time->setsGanhos += setsGanhos;
    time->setsPerdidos += setsPerdidos;
    time->pontosGanhos += pontosGanhos;
    time->pontosPerdidos += pontosPerdidos;
                        }
                        
/* Atualiza os atributos relativos as partidas */
void atualizaPartida(time_t *timeGanhador, time_t *timePerdedor, 
                     int diferencaSets, int confrontoDireto[][6]) {
    timeGanhador->vitorias++;
    
    if (diferencaSets > 1)
        timeGanhador->pontos += 3;
    else {
        timeGanhador->pontos += 2;
        timePerdedor->pontos += 1;
    }
    
    confrontoDireto[timeGanhador->indice][timePerdedor->indice] = 1;
    confrontoDireto[timePerdedor->indice][timeGanhador->indice] = -1;
}

/*Verifica se o time lido ja foi armazenado*/
void procura_nomes(time_t *timesChave, int *ocupado, int *j)
{
    int i, flag = 0;
    char aux[21];
    
    scanf(" ");
    scanf("%s", aux);
    
    for(i = 0; (i < 6) && (flag == 0); i++)
    {   
        if((strcmp(aux, timesChave[i].nome) != 0) 
            && (ocupado[i] == 0))  
        {
            strcpy(timesChave[i].nome, aux);
            *j = i;
            timesChave[i].indice = i;
            flag = 1;
            ocupado[i] = 1;
        }
        else if(strcmp(aux, timesChave[i].nome) == 0)
        {
            *j = i;
            timesChave[i].indice = i;
            flag = 1;
            ocupado[i] = 1;
        }
    }
}

/* Le os resultados das partidas entre todos os times de uma chave */
void leResultadosChave(time_t timesChave[], int confrontoDireto[][6]) {
    
    int i = 0, j, k, l = 0, flag2 = 0, pontos1 = 0, pontos2 = 0;
    int sets1 = 0, sets2 = 0, ocupado[6], pontos_totais1, pontos_totais2;
    
    for(i = 0; i < 6; i++)
    {
        timesChave[i].indice = 0;
        timesChave[i].pontos = 0;
        timesChave[i].vitorias = 0;
        timesChave[i].pontosGanhos = 0;
        timesChave[i].pontosPerdidos = 0;
        timesChave[i].setsGanhos = 0;
        timesChave[i].setsPerdidos = 0;
    }
    
    for(i = 0; i < 6; i++)
    {
        ocupado[i] = 0;
    }
    
    for(l = 0; l < 15; l++)
    {    
        pontos_totais1 = 0;
        pontos_totais2 = 0;
        flag2 = 0;
        sets1 = 0;
        sets2 = 0;
        
        procura_nomes(timesChave, ocupado, &j);
        procura_nomes(timesChave, ocupado, &k);
        
        scanf(" ");
        for(i = 0; flag2 == 0; i++)
        {
            scanf("%d-%d", &pontos1, &pontos2);
            pontos_totais1 += pontos1;
            pontos_totais2 += pontos2;
            
            if(pontos1 > pontos2)
            {
                sets1++;
            }
            else
            {
                sets2++;
            }
            
            if((sets1 == 3) || (sets2 == 3))
            {
                flag2 = 1;
            }
        }
        
        atualizaSetsPontos(&timesChave[j], sets1, sets2, pontos_totais1, 
                           pontos_totais2);
        
        atualizaSetsPontos(&timesChave[k], sets2, sets1, pontos_totais2, 
                           pontos_totais1);
        
        if(sets1 > sets2)
        {
            atualizaPartida(&timesChave[j], &timesChave[k], 
                            (sets1 - sets2), confrontoDireto);
        }
        else
        {
            atualizaPartida(&timesChave[k], &timesChave[j], 
                            (sets2 - sets1), confrontoDireto);
        } 
    }
}

/* Ordena o vetor de times */
void ordenaTimes(time_t times[], int n, int confrontoDireto[][6]) {
    
    int i, j, k;
    float razao_sets1, razao_sets2, razao_pontos1, razao_pontos2;
    time_t aux;
    
    /*Ordena por meio do numero de pontos*/
    for(i = 0; i < n; i++)
    {
        j = i;
        
        for(k = i + 1; k < n; k++)
        {
            if(times[j].pontos < times[k].pontos)
            {
                j = k;
            }
        }
        
        aux = times[i];
        times[i] = times[j];
        times[j] = aux;
    }
    
    /*Ordena pelo numero de vitorias*/
    for(i = 0; i < n; i++)
    {
        if(times[i].pontos == times[i + 1].pontos)
        {
            j = i;
            
            for(k = i + 1; (times[k].pontos == times[i].pontos) && (k < n); k++)
            {
                if(times[k].vitorias > times[j].vitorias)
                {
                    j = k;
                }
            }
            
            aux = times[i];
            times[i] = times[j];
            times[j] = aux;
        }
    }   

    /*Ordena pela razao de sets*/
    for(i = 0; i < n; i++)
    {
        if((times[i].pontos == times[i + 1].pontos) && 
           (times[i].vitorias == times[i + 1].vitorias))
        {
            j = i;
            
            for(k = i + 1; (times[i].pontos == times[k].pontos) && 
               (times[i].vitorias == times[k].vitorias) && (k < n); k++)
            {
                razao_sets1 = (float)times[k].setsGanhos / 
                         (times[k].setsGanhos + times[k].setsPerdidos);
                razao_sets2 = (float)times[j].setsGanhos / 
                         (times[j].setsGanhos + times[j].setsPerdidos);
                         
                if(razao_sets1 > razao_sets2)
                {
                    j = k;
                }
            }
            
            aux = times[i];
            times[i] = times[j];
            times[j] = aux;
        }
    }
    
    /*Ordena pela razao de pontos*/
    for(i = 0; i < n; i++)
    {
        razao_sets1 = (float)times[i].setsGanhos / 
                 (times[i].setsGanhos + times[i].setsPerdidos);
        razao_sets2 = (float)times[i + 1].setsGanhos / 
                 (times[i + 1].setsGanhos + times[i + 1].setsPerdidos);
                 
        if((times[i].pontos == times[i + 1].pontos) && 
           (times[i].vitorias == times[i + 1].vitorias) &&
           (razao_sets1 == razao_sets2))
        {
            j = i;
            k = i + 1;
            while((times[i].pontos == times[k].pontos) && 
                 (times[i].vitorias == times[k].vitorias) && 
                 (razao_sets1 == razao_sets2) && (k < n))
            {    
                  razao_pontos1 = (float)(times[k].pontosGanhos) /
                             (times[k].pontosGanhos + times[k].pontosPerdidos); 
                  razao_pontos2 = (float)(times[j].pontosGanhos) /
                             (times[j].pontosGanhos + times[j].pontosPerdidos); 
                             
                  if(razao_pontos1 > razao_pontos2)
                  {
                      j = k;
                  }
                  
                  k++;
                  razao_sets1 = (float)times[i].setsGanhos / 
                                (times[i].setsGanhos + times[i].setsPerdidos);
                  razao_sets2 = (float)times[k].setsGanhos / 
                                (times[k].setsGanhos + times[k].setsPerdidos);
            }
            
            aux = times[i];
            times[i] = times[j];
            times[j] = aux;
        }
    }
    
    /*Ordena pelo confronto direto*/
    for(i = 0; i < n; i++)
    {
        j = i + 1;
        razao_sets1 = (float)times[i].setsGanhos / 
                      (times[i].setsGanhos + times[i].setsPerdidos);
        razao_sets2 = (float)times[j].setsGanhos / 
                      (times[j].setsGanhos + times[j].setsPerdidos);
        razao_pontos1 = (float)(times[i].pontosGanhos) /
                        (times[i].pontosGanhos + times[i].pontosPerdidos); 
        razao_pontos2 = (float)(times[j].pontosGanhos) /
                        (times[j].pontosGanhos + times[j].pontosPerdidos);
                        
        if((times[i].pontos == times[j].pontos) && 
          (times[i].vitorias == times[j].vitorias) &&
          (razao_sets1 == razao_sets2) && (razao_pontos1 == razao_pontos2))
        {
            if(confrontoDireto[times[j].indice][times[i].indice] == 1)
            {
                aux = times[i];
                times[i] = times[j];
                times[j] = aux;
            }
        }
    }
}

int main() {
   /* variaveis de entrada */
   time_t timesChaveA[6], timesChaveB[6];
   /* variaveis auxiliares */
   int i, confrontosChaveA[6][6], confrontosChaveB[6][6];

   /* le entrada */
   leResultadosChave(timesChaveA, confrontosChaveA);
   leResultadosChave(timesChaveB, confrontosChaveB);
    
   
   /*ordena os vetores de times na ordem de classificacao */
   ordenaTimes(timesChaveA, 6, confrontosChaveA);
   ordenaTimes(timesChaveB, 6, confrontosChaveB);

   /* imprime a saida */
   for (i = 0; i < 4; i++) {
      printf("%s x %s\n", timesChaveA[i].nome, timesChaveB[3-i].nome);
   }
   
   return 0;
}
