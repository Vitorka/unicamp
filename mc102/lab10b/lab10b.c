/*Nome: Vitor Kaoru Aoki   
  RA: 178474
*/

#include <stdio.h>
#include <stdlib.h>

void ordena(int notas[], int max_indiv);

int main(){
    
    int i, j, k, num_hom, num_mulh, dif_hab, aux, 
    max_duplas = 0, homem_escolhido = 0;
    int *homens, *mulheres;
    
    scanf("%d %d %d", &num_hom, &num_mulh, &dif_hab);
    
    homens = malloc(num_hom * sizeof(int));
    mulheres = malloc(num_mulh * sizeof(int));
    
    for(i = 0; i < num_hom; i++)
    {
        scanf("%d", &homens[i]);
    }
    
    for(i = 0; i < num_mulh; i++)
    {
        scanf("%d", &mulheres[i]);
    }
    
    /*Ordena os vetores de notas dos homens e das mulheres, a fim de garantir 
    que o numero maximo de casais sera escolhido*/
    ordena(homens, num_hom);
    ordena(mulheres, num_mulh);
    
    for(i = 0; i < num_hom; i++, homem_escolhido = 0)
    {
        for(j = 0; (j < num_mulh) && (homem_escolhido == 0); j++)
        {
            if(homens[i] - mulheres[j] < 0)
            {
                aux = mulheres[j] -homens[i];
            }
            else
            {
                aux = homens[i] - mulheres[j];
            }
            
            if(aux <= dif_hab)
            {
                max_duplas++;
                num_mulh--;
                
                /*Assim que um casal eh formado, elimina a possibilidade deles 
                serem escolhidos novamente*/
                homem_escolhido = 1;
                for(k = j; k < num_mulh; k++)
                {
                    mulheres[k] = mulheres[k + 1];
                }
            }
        }
    }
    
    printf("Numero maximo de duplas equilibradas = %d\n", max_duplas);
    
    free(homens);
    free(mulheres);
    
    return 0;
}

void ordena(int notas[], int max_indiv)
{
    int i, j, k, aux;
    
    for(i = 0; i < max_indiv - 1; i++)
    {   
        k = i;
        for(j = i + 1; j < max_indiv; j++)
        {
            if(notas[k] > notas[j])
            {
                k = j;
            }
        }
        aux = notas[i];
        notas[i] = notas[k];
        notas[k] = aux;
    }
}
            
    
    