/*Nome: Vitor Kaoru Aoki
  RA: 178474
*/

#include <stdio.h>

typedef struct
{
    char nome[60];
    char sexo;
    int idade;
    float altura;
} caracteristicas;
    

int main()
{
    FILE *arqin, *arqout;
    int i;
    char aux;
    caracteristicas caract[2];
    
    arqin = fopen("arq01.txt", "r");
    arqout = fopen("arq02.txt", "w");
    
    for(i = 0; i < 2; i++)
    {   
        fscanf(arqin, "%s", caract[i].nome);
        fscanf(arqin, "%c", &aux);
        fscanf(arqin, "%c", &caract[i].sexo);
        fscanf(arqin, "%d", &caract[i].idade);
        fscanf(arqin, "%f", &caract[i].altura);
        fscanf(arqin, "%c", &aux);
    }
    fclose(arqin);
    
    for(i = 0; i < 2; i++)
    {
        fprintf(arqout, "%s\n", caract[i].nome);
        fprintf(arqout, "%c\n", caract[i].sexo);
        fprintf(arqout, "%d\n", caract[i].idade);
        fprintf(arqout, "%.2f\n", caract[i].altura);
        fprintf(arqout, "%c", aux);
    }
    fclose(arqout);
    
    return 0;
}