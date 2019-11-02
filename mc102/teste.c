#include <stdlib.h>
void atualiza(int vetor[], int n) {
int i;
for (i = 0; i < n; i++)
vetor[i-1]++;
}
int main() {
int *vetor, i, n = 10;
vetor = malloc(n * sizeof(int));
for (i = 0; i < n; i++)
vetor[i+1] = i;
atualiza(vetor, n);
return 0;
}