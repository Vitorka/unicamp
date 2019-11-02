/*Nome: Vitor Kaoru Aoki   
  RA: 178474
*/

#include <stdio.h>

/*O programa analisa a quantidade de sub-bombas formadas a partir da explosao 
de uma bomba inicial, e contabiliza a altura maxima da arvore que representa as 
explosoes dessa bomba*/
int arvore_queima()
{
   int i, sub_bomba, altura, altura_max = 0;
   
   scanf("%d", &sub_bomba);
   
   /*Verifica se a sub-bomba atual explodiu sem que desse origem a outras 
   sub-bombas*/
   if(sub_bomba == 0)
   {
       return 1;
   }
   else
   {
       /*Caso outras sub-bombas tenham surgido como resultado da explosao da 
       sub-bomba atual, chama recursivamente a funcao*/
       for(i = 0; i < sub_bomba; i++)
       {
            altura = arvore_queima();
            
            if(altura > altura_max)
            {
                altura_max = altura;
            }
       }
       
       return altura_max + 1;
       
   }
}

int main()
{
    int altura;
    
    altura = arvore_queima();
    
    printf("%d\n", altura);

    return 0;  
}
