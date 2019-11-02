#include <stdio.h>
#include <math.h>

int main(){

    int e, y, dolar, x;

    scanf("%d", &dolar);
    scanf("%d", &x);

    
        
        for(e = 0; y < dolar; e++){
        printf("%d", e);
            y = pow(x, e);
                
        
        }

        dolar = dolar - pow(x, (e - 2));
    
    printf("%d\n", e);
    printf("%d\n", dolar);

    return 0;

}