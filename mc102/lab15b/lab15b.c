/*Nome: Vitor Kaoru Aoki
  RA: 178474
*/

#include <stdio.h>
# define max 10

int main()
{
    int permut[max][max], permut_aux[max], tam_permut, contador = 0;
    int i, j = 0, k = 0, aux = 0, aux2;
    int l, m;
        
    scanf("%d", &tam_permut);
    
    for(i = 0; i < max; i++)
    {
        for(j = 0; j < max; j++)
        {
            permut[i][j] = 0;
        }
    }
    
    j = 0;
    
    /*Armazena os numeros de entrada num vetor auxiliar*/
    for(i = 0; i < tam_permut; i++)
    {
        scanf("%d", &permut_aux[i]);
    }
    
    /*Verifica a existencia de breackpoints*/
    for(i = 0; i < tam_permut; i++)
    {
        if((permut_aux[i + 1] - permut_aux[i]) == 1)
        {
            permut[j][k] = permut_aux[i];
            k++;
        }
        else
        {
            permut[j][k] = permut_aux[i];
            j++;
            k = 0;
        }
    }
    
    aux2 = j;
    
    /*Por meio de insertion, descobre qual a distancia a partir do numero de 
    trocas realizadas*/
    for(i = 0; i < aux2; i++)
    {
        aux = permut[i][0];
        
        for(j = i + 1; j < aux2; j++)
        {
            if(aux > permut[j][0])
            {
                aux = permut[j][0];
                m = j;
            }
        }
        
        if(aux != permut[i][0])
        {
            for(l = m; l > i; l--)
            {
                permut[l][0] = permut[l - 1][0];
            }
            permut[i][0] = aux;
            contador++;
        }    
    }
    
    printf("%d\n", contador);
    
    return 0;
}
        