/*Nome: Vitor Kaoru Aoki
  RA: 178474
*/

#include <stdio.h>

void adicao(int *x, int *y, int *resultado);
void subtracao(int *x, int *y, int *resultado);
void multiplicacao(int *x, int *y, int *resultado);

int main(){
    
    int n1, n2, result;
    char operacao;
    
    scanf("%d %d", &n1, &n2);
    scanf(" %c", &operacao);
    
    if(operacao == 'A')
    {
        adicao(&n1, &n2, &result);
    }
    else if(operacao == 'S')
    {
        subtracao(&n1, &n2, &result);
    }
    else if(operacao == 'M')
    {
        multiplicacao(&n1, &n2, &result);
    }
    
    printf("resultado = %d\n", result);
    
    return 0;
}

void adicao(int *x, int *y, int *resultado)
{
    *resultado = *x + *y;
}
void subtracao(int *x, int *y, int *resultado)
{
    *resultado = *x - *y;
}
void multiplicacao(int *x, int *y, int *resultado)
{
    *resultado = (*x) * (*y);
}