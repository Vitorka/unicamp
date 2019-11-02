#include <stdio.h>

void muda_vetor(int vetor[]);

int main()
{
    int vetor[10], i;
    
    for(i = 0; i < 10; i++)
    {
        vetor[i] = 1;
    }
    
    for(i = 0; i < 10; i++)
    {
        printf("vetor[%d] = %d\n", i + 1, vetor[i]);
    }
    printf("\n");
    
    muda_vetor(vetor);
    
    for(i = 0; i < 10; i++)
    {
        printf("vetor[%d] = %d\n", i + 1, vetor[i]);
    }
    
    return 0;
}

void muda_vetor(int vetor[])
{
    int i, n = 0;
   
    for(i = 0; i < 10; i++, n++)
    {
        vetor[i] = vetor[i] + n;
    }
}