#include "impressoes.h"

//Imprime o mapa de memoria na saida padrao ou no arquivo de saida
void imprime_mapa(mapa *mapa_memoria, int argc, FILE *arqs) {
    int i, j;
    char *aux;
    
    if(argc == 2) {
        for(i = 0; i < 1024; i++, j = 0) {
            if(mapa_memoria[i].palavra[0] != '*') {
                aux = dec_para_hexa(i);
                printf("%s ", &aux[7]);
                for(j = 0; j < 10; j++){
                    printf("%c", mapa_memoria[i].palavra[j]);
                    if((j == 1) || (j == 4) || (j == 6)){
                        printf(" ");
                    }
                }
                free(aux);
                printf("\n");
            }
        }
    } else {
        
        for(i = 0; i < 1024; i++, j = 0) {
            if(mapa_memoria[i].palavra[0] != '*') {
                
                fprintf(arqs, "%s ", &dec_para_hexa(i)[7]);
                
                for(j = 0; j < 10; j++){
                    
                    fprintf(arqs, "%c", mapa_memoria[i].palavra[j]);
                    
                    if((j == 1) || (j == 4) || (j == 6)){
                        fprintf(arqs, "%s", " ");
                    }
                }        
                fprintf(arqs, "%s", "\n");
            }
        }
        
    }
}

//Imprime a mensagem de erro na saida padrao ou no arquivo de saida e termina o programa
void imprime_erros(int num_linha, char *mensagem_erro, char *argumento, int argc, FILE *arqs, FILE *arqe, 
                   mapa *mapa_memoria, rotulos *inicio_rotulos, sets *inicio_sets) {
    
    if(argc == 2) {
        printf("ERROR on line %d\n%s%s!\n", num_linha, argumento, mensagem_erro);
    } else {
        fprintf(arqs, "ERROR on line %d\n%s!\n", num_linha, mensagem_erro);
    }
    
    free(mapa_memoria);
    desaloca_rotulos(inicio_rotulos);
    desaloca_sets(inicio_sets);
    
    fclose(arqe);
    if(argc == 3){
        fclose(arqs);
    }
    exit(0);
}

