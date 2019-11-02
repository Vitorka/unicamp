#include <stdio.h>
int main() {
char string1[81], string2[161];
int i = 0, j = 0;
printf("Digite uma string: ");
fgets(string1, 81, stdin);
printf("Digite outra string: ");
fgets(string2, 81, stdin);
/* equivalente a strcat(string2, string1) da biblioteca string.h */
while (string2[i])
i++;
do {
string2[i++] = string1[j];
} while (string1[j++]);
printf("%s", string2);
return 0;
}