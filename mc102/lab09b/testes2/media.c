#include <stdio.h>
#include <stdlib.h>
#define max_jog 50

int main()
{    
    int i, j, num_jog, descart;
    float notas[max_jog][max_jog], medias[max_jog];
    
    scanf("%d %d", &num_jog, &descart);
    
    for(i = 0; i < num_jog; i++)
    {
        for(j = 0; j < num_jog; j++)
        {
            scanf("%f", &notas[i][j]);
        }
    }
    
    for(i = 0; i < num_jog; i++)
    {
        medias[i] = 0;
    }
    
    for(j = 0; j < num_jog; j++)
    {
        for(i = 0; i < num_jog; i++)
        {
            medias[j] += notas[i][j]/num_jog;
        }
    }

    for(i = 0; i < num_jog; i++)
    {
        printf("media[%d] = %.3f\n", i + 1, medias[i]);
    }
    
    return 0;
}
