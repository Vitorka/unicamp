/*Nome: Vitor Kaoru Aoki
  RA: 178474
*/

#include <stdio.h>

/*A partir de duas palavras dadas, verifica se a primeira palavra e 
subsequencia da segunda*/
int main() {
    
    char palavra1[21], palavra2[21];
    int i, j, k, num_p1 = 0, num_p2 = 0, contador = 0, num_caract1 = 0, linhas;
       
    scanf("%d ", &linhas);
   
    for(k = 0; k < linhas; k++, num_caract1 = 0, contador = 0) {
        scanf("%s", palavra1); 
        scanf("%s", palavra2);
        
        /*Conta o numero de caracteres da primeira palavra*/
        for(i = 0; palavra1[i] != '\0'; i++) {
            num_caract1++;
        }
        
        /*Transformando cada caractere das palavras dadas, em numeros, compara 
        se os caracteres da palavra1 estao presentes em ordem na palvra2*/
        for(j = 0, i = 0; palavra2[j] != '\0'; j++) {
            num_p1 = palavra1[i];
            num_p2 = palavra2[j];
                 
            if(num_p1 == num_p2) { 
                i++;
                contador++;    
            }
        }
        
        /*Caso o numero do contador seja igual ao numero de caracteres da 
        palavra1, a primeria palavra e uma subsequencia da segunda*/
        if(contador == num_caract1) {
            printf("Sim\n");
        } else {
            printf("Nao\n");
        }      
   }
   return 0;      
}