#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char materia[81];
    float p1;
    float p2;
    float p3;
    float peso1;
    float peso2;
    float peso3;
    float nota_final;
    float med_min;
} media;

int main()
{
    media *final;
    int i, num_materias;
    float exame, media;
    
    printf("Entre com o numero de materias: ");
    scanf("%d", &num_materias);
    
    final = malloc(num_materias * sizeof(media));
    
    printf("\n");
    for(i = 0; i < num_materias; i++)
    {
        printf("Materia: ");
        scanf("%s", final[i].materia);
        
        printf("Media minima da materia: ");
        scanf(" ");
        scanf("%f", &final[i].med_min);
        printf("\n");
        
        printf("Nota P1: ");
        scanf("%f", &final[i].p1);
        printf("Peso P1: ");
        scanf("%f", &final[i].peso1);
        printf("\n");
        
        printf("Nota P2: ");
        scanf("%f", &final[i].p2);
        printf("Peso P2: ");
        scanf("%f", &final[i].peso2);
        printf("\n");
        
        printf("Nota P3: ");
        scanf("%f", &final[i].p3);
        printf("Peso P3: ");
        scanf("%f", &final[i].peso3);
        printf("\n");
    }
    
    for(i = 0; i < num_materias; i++)
    {
        if((final[i].p1 == -1) && (final[i].p2 == -1) && (final[i].p3 == -1))
        {
            printf("Materia: %s\n", final[i].materia);
            printf("Provas ainda nao iniciadas!!\n");
            printf("Nota minima necessaria em cada prova para "); 
            printf("aprovacao: %.2f\n", final[i].med_min);
            printf("\n");
        }
        else if((final[i].p2 == -1) && (final[i].p3 == -1))
        {   
            printf("Materia: %s\n", final[i].materia);
            printf("P2 e P3 ainda nao realizadas!!\n");
            
            media = (float)(final[i].p1 * final[i].peso1) / 
                           (final[i].peso1 + final[i].peso2 + final[i].peso3);
            
            printf("Media parcial: %.2f\n", media);
            
            final[i].nota_final = ((final[i].med_min * 
                                   (final[i].peso1 + final[i].peso2 +
                                    final[i].peso3)) - 
                                  (final[i].p1 * final[i].peso1))/ 
                                  (final[i].peso2 + final[i].peso3);
                                  
            printf("Nota minima necessaria na P2 e na P3 para aprovacao: ");
            printf("%.2f\n", final[i].nota_final);
            printf("\n");
        }
        else if(final[i].p3 == -1)
        {
            printf("Materia: %s\n", final[i].materia);
            printf("P3 ainda nao realizada!!\n");
            
            media = (float)((final[i].p1 * final[i].peso1) + (final[i].p2* 
                                                              final[i].peso2)) /
                    (final[i].peso1 + final[i].peso2 + final[i].peso3);
            
            printf("Media parcial: %.2f\n", media);
            
            if(media >= final[i].med_min)
            {
                printf("Aprovado sem a necessidade de realizacao da P3!!\n");
                printf("\n");
            }
            else
            {
                final[i].nota_final = ((final[i].med_min * 
                                       (final[i].peso1 + final[i].peso2 +
                                        final[i].peso3)) -
                                       ((final[i].p1 * final[i].peso1) + 
                                        (final[i].p2 * final[i].peso2))) /
                                      (final[i].peso3);
                if(final[i].nota_final <= 10)
                {
                    printf("Nota minima necessaria na P3 para aprovacao: ");
                    printf("%.2f\n", final[i].nota_final);
                    printf("\n");
                }
                else
                {
                    printf("Exame mesmo com a realizacao da P3\n");
                    printf("\n");
                }
            }
        }
        else
        {
            printf("Materia: %s\n", final[i].materia);
            
            final[i].nota_final = (final[i].p1 * final[i].peso1) +
                                  (final[i].p2 * final[i].peso2) +
                                  (final[i].p3 * final[i].peso3) /
                                  (final[i].peso1 + final[i].peso2 + 
                                   final[i].peso3);
                                  
            if(final[i].nota_final >= 5.0)
            {
                printf("Nota final: %.2f\n", final[i].nota_final);
                printf("Aprovado!!\n");
                printf("\n");
            }
            else if((final[i].nota_final < 5.0) && (final[i].nota_final >= 2.5))
            {
                printf("Nota final: %.2f\n", final[i].nota_final);
                printf("Exame!!\n");
                
                exame = (final[i].med_min * 2) - (final[i].nota_final);
                
                printf("Nota minima necessaria no exame: %.2f\n", exame);
                printf("\n");
            }
            else if(final[i].nota_final < 2.5)
            {
                printf("Reprovado!!\n");
                printf("\n");
            }
        }
    }
    return 0;
}