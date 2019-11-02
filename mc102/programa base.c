/*Nome: Vitor Kaoru Aoki
  RA: 178474
*/

#include <stdio.h>
# define max 10

int main()
{
    int permut[max][max], permut_aux[max], aux;
    int i, j = 0, k = 0;
    
    scanf("%d", &tam_permut);
    
    for(i = 0; i < max; i++)
    {
        for(j = 0; j < max; j++)
        {
            permut[i][j] = 0;
        }
    }
    
    j = 0;
    
    for(i = 0; i < tam_permut; i++)
    {
        scanf("%d", &permut_aux[i]);
    }
    
    for(i = 0; i < tam_permut; i++)
    {
        if((permut_aux[i + 1] - permut_aux[i]) == 1)
        {
            permut[j][k] = permut_aux[i];
            k++
        }
        else
        {
            permut[j][k] = permut_aux[i];
            j++;
        }
    }
    
    for(i = 0; i < max; i++)
    {
        for(j = 0; j < max; j++)   
        {
            printf("%d ", permut[i][j]);
        }
        printf("\n");
    }
    
    
    
  
    return 0;
}