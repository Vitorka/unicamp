#include <stdio.h>
int main() {
unsigned int n, fator = 2;
printf("Digite um numero inteiro positivo: ");
scanf("%u", &n);
printf("%d = 1", n);
while (n > 1) {
if ((n % fator) == 0) {
printf(" x %d", fator);
n = n / fator;
} else
fator++;
}
printf("\n");
return 0;
}