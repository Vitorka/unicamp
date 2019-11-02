#include <stdio.h>

int main()
{
    FILE *arqin;
    int num_jog;
    
    arqin = fopen(nomeArqEstat, "rb");
    
    fread(&num_jog, sizeof(int), 1, arqin);
    
    printf("%d\n", num_jog);
    
    fclose(arqin);
    
    return 0;
}