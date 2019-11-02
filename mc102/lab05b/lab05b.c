/*Nome: Vitor Kaoru Aoki
  RA: 178474
*/

#include <stdio.h>
/*O programa, a partir de duas palavras dadas, calcula a distancia de Tchonsky 
entre elas*/
int main(){
    
    char palavra1[100], palavra2[100];
    int i, j, k, x, dist, num_caract1 = 0, num_caract2 = 0, caract_comum = 0, 
    vetor[26];
    
    for(i = 0; i < 26; i++) {          
        vetor[i] = 0;          
    }
    
    scanf("%s", palavra1);
    scanf("%s", palavra2);
    
    /*Conta o numero de caracteres da palavra1*/
    for(i = 0; palavra1[i] != '\0'; i++) {      
        num_caract1++;     
    }
    
    /*Conta o numero de caracteres da palavra2*/
    for(i = 0; palavra2[i] != '\0'; i++) {    
        num_caract2++;  
    }
    
    /*Por meio de um vetor, conta o numero de vezes que cada caractere da 
    palavra1 aparece, fazendo equivalencia entre letras maiusculas e 
    minusculas*/
    for(j = 0; palavra1[j] != '\0'; j++) {
        
        if((palavra1[j] >= 65) && (palavra1[j] <= 90)) {
            vetor[palavra1[j] - 'A']++;
        } else if ((palavra1[j] >= 97) && (palavra1[j] <= 122)) {
            vetor[palavra1[j] - 'a']++;            
        }   
    }
    
    /*Usando uma variavel x, determina o valor correspondente do 
    caractere da palavra2 e utiliza-o para identificar se esse caractere se 
    encontra presente na palavra1*/
    for(k = 0; palavra2[k] != '\0'; k++) {
        
        if((palavra2[k] >= 65) && (palavra2[k] <= 90)) {
            x = palavra2[k] - 'A';
        } else if ((palavra2[k] >= 97) && (palavra2[k] <= 122)) {
            x = palavra2[k] - 'a';            
        }   
        
        /*Conta o numero de caracteres em comum entre as duas palavras*/
        if(vetor[x] != 0) {    
            vetor[x]--;
            caract_comum++;
        }    
    }
    
    dist = (num_caract1 + num_caract2) - (2 * caract_comum);
    printf("Distancia de Tchonsky = %d\n", dist);
  
    return 0;       
}