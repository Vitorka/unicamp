/*Nome: Vitor Aoki
  RA: 178474
*/

#include <stdio.h>

int main()
{
    int a, b, c, e, x;
    
    /*Definindo os valores das constantes a, b e c*/
    
    printf("Digite tres valores para as constantes a, b e c: \n");
    scanf("%d %d %d", &a, &b, &c);

    /*Definindo o valor da variavel x*/
    
    printf("Digite um valor para a variavel x: \n");
    scanf("%d", &x);

    /*Resolucao da funcao de segundo grau*/
    
    e = (a * x * x) + (b * x) + (c);

    printf("f(x) = %d\n", e);

    return 0;
}