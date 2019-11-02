#include <stdio.h>

struct aluno
{
    char nome[81];
    int idade;
    char sexo;
};

int main()
{
    int i;
    struct aluno a[3];
    
    for(i = 0; i < 3; i++)
    {
        printf("Entre com o nome: ");
        scanf(" ");
        fgets(a[i].nome, 81, stdin);
    
        printf("Entre com a idade: ");
        scanf("%d", &a[i].idade);
    
        printf("Entre com o sexo: ");
        scanf(" ");
        scanf("%c", &a[i].sexo);
        
        printf("\n");
    }
        
    for(i = 0; i < 3; i++)
    {
        printf("Nome: %s", a[i].nome);
        printf("Idade %d\n", a[i].idade);
        printf("Sexo: %c\n", a[i].sexo);
    }
    
    return 0;
}