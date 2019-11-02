#include <stdio.h>

int main() {
    long int a = 1;
    long int b = 1;
    long int aux;
    
    int n;
    
    scanf("%d", &n);
    
    if(n == 0) {
        printf("%d\n", 0);
    } else {
        n -= 2;
        for(int i = 0; i < (n); i++) {
            aux = a;
            a = b;
            b = aux + b;
        }
        
        printf("%ld\n", b);
    }
    
    return 0;
}
