/*Nome: Vitor Kaoru Aoki
  RA: 178474
*/

#include <stdio.h>
#include <math.h>

int main(){
    
    int a, b;
    double x, y;

    scanf("%d %d", &b, &a);    
    
    /*Calculo do valor original*/
    
    if (1 <= a && a <= 10){
        
        x = 17.34;  
    }
    else if (11 <= a && a <=20){
   
        x = 17.34 + ((a - 10) * 2.41);
    }
    else if (21 <= a && a <= 50){

        x = 17.34 + (10 * 2.41) + ((a - 20) * 3.70);
    }
    else if (a >= 50){
    
        x = 17.34 + (10 * 2.41) + (30 * 3.70) + ((a - 50) * 4.43);
    }

    printf("Valor original = %.2f\n", x);

    /*Calculo do valor com desconto e com a multa*/

    if (a <= (0.8 * b)){

        y = 0.7 * x;
    }
    else if (a > (0.8 * b) && a <= (0.85 * b)){
        
        y = 0.8 * x;
    }
    else if (a > (0.85 * b) && a <= (0.9 * b)){

        y = 0.9 * x;
    }
    else if (a > (0.9 * b) && a <= (1.05 *  b)){

        y = x;
    }
    else if (a > (1.05 * b) && a < (1.2 * b)){

        y = 1.4 * x;
    }
    else if (a >= (1.2 * b)){
        
        y = 2 * x;
    }
    
    printf("Valor final = %.2f\n", y);

    return 0;
}