/*Nome: Vitor Kaoru Aoki
  RA: 178474
*/

#include <stdio.h>

int main(){
    
    int n, indiv[9], i, total = 0;
    char v;
    indiv[0] = 0;
    indiv[1] = 0;
    indiv[2] = 0;
    indiv[3] = 0;
    indiv[4] = 0;
    indiv[5] = 0;
    indiv[6] = 0;
    indiv[7] = 0;
    indiv[8] = 0;
    
    scanf("%d", &n);
   
    for(i = 1, scanf("%c", &v); i <= n; i++){
                
        do{
            
            
           
            if(v == '1'){
               
               indiv[0]++;
               total++;
            }
            else if(v == '2'){
               
               indiv[1]++;
               total++;
            }
            else if(v == '3'){
               
               indiv[2]++;
               total++;
            }
            else if(v == '4'){
               
               indiv[3]++;
               total++;
            }
            else if(v == '5'){
               
               indiv[4]++;
               total++;
            } 
            else if(v == '6'){
               
               indiv[5]++;
               total++;
            } 
            else if(v == '7'){
               
               indiv[6]++;
               total++;
            }
            else if(v == '8'){
               
               indiv[7]++;
               total++;
            }
            else if(v == '9'){
               
               indiv[8]++;
               total++;
            }
        
        scanf("%c", &v);
        }while(v != '\n');
        
        
    }
    
        printf("Total: %d individuos\n", total);
        if(indiv[0] != 0){
            printf("Total da casta 1: %d\n", indiv[0]);
        }
        if(indiv[1] != 0){
            printf("Total da casta 2: %d\n", indiv[1]);
        }
        if(indiv[2] != 0){
            printf("Total da casta 3: %d\n", indiv[2]);
        }
        if(indiv[3] != 0){
            printf("Total da casta 4: %d\n", indiv[3]);
        }
        if(indiv[4] != 0){
            printf("Total da casta 5: %d\n", indiv[4]);
        }
        if(indiv[5] != 0){
            printf("Total da casta 6: %d\n", indiv[5]);
        }
        if(indiv[6] != 0){
            printf("Total da casta 7: %d\n", indiv[6]);
        }
        if(indiv[7] != 0){
            printf("Total da casta 8: %d\n", indiv[7]);
        }
        if(indiv[8] != 0){
            printf("Total da casta 9: %d\n", indiv[8]);
        }
    
    
    return 0;
}