#include "operacoes-montador.h"
#include "conversoes.h"
#include "impressoes.h"

//Insere um novo rotulo a lista de rotulos
rotulos *insere_rotulos(char *nome_rotulo, rotulos *inicio, long int end_mapa, int pos_mont, int rotulo_existente) {
    
    char *hexa = dec_para_hexa(end_mapa);
    
    rotulos *new_rotulo;
    new_rotulo = (rotulos *)malloc(sizeof(rotulos));
    
    new_rotulo->end_mapa = end_mapa;
    new_rotulo->rotulo_existente = rotulo_existente;
    new_rotulo->pos_mont = pos_mont;
    strcpy(new_rotulo->nome_rotulo, nome_rotulo);
    strcpy(new_rotulo->endereco, &hexa[7]);
    
    if(inicio == NULL) {
        new_rotulo->prox = NULL;
    } else {
        new_rotulo->prox = inicio;
    }
    
    free(hexa);
    return new_rotulo;
}

//Insere um novo set, na lista de .set
sets *insere_sets(char *simbolo, char *valor, sets *inicio, int set_existente) {
    
    for(int i = 0; (i < strlen(valor)) && (set_existente); i++) {
        valor[i] = toupper(valor[i]);
    }
    
    sets *new_set;
    new_set = (sets *)malloc(sizeof(sets));
    new_set->set_existente = set_existente;
    strcpy(new_set->simbolo, simbolo);
    strcpy(new_set->valor, valor);
    
    if(inicio == NULL) {
        new_set->prox = NULL;
    } else {
        new_set->prox = inicio;
    }
    
    return new_set;
}

//Adiciona os .word e .wfill ao mapa de memoria
void adiciona_palavras(char *palavra, mapa *mapa_memoria, long int linha) {
    int i, j;
    
    for(i = strlen(palavra) - 1, j = strlen(mapa_memoria[linha].palavra) - 1; (i >= 0) && (j >= 0); i--, j--) {
        mapa_memoria[linha].palavra[j] = toupper(palavra[i]);
    }
}

//Adiciona uma instrucao em sua respectiva posicao
int adiciona_instrucao(char *opcode, char *endereco, mapa *mapa_memoria, long int linha, int dir_esq) {
    
    int i, j;
    
    //Veririca se adicionara a instrucao a esquerda
    if(dir_esq == 1) {
        for(i = 0; i < 2; i++) {
            mapa_memoria[linha].palavra[i] = opcode[i];
        }
        
        for(i = 2, j = 0; i < 5; i++, j++) {
            mapa_memoria[linha].palavra[i] = endereco[j];
        }
        return 1;
    }
    //Verifica se adicionara a instrucao a direita
    else if((dir_esq == 2) && (mapa_memoria[linha].palavra[0] != '*')) {
        
        for(i = 5, j = 0; i < 7; i++, j++) {
            mapa_memoria[linha].palavra[i] = opcode[j];
        }
        
        for(i = 7, j = 0; i < 10; i++, j++) {
            mapa_memoria[linha].palavra[i] = endereco[j];
        }
        return 1;
    } else {
        return 0;
    }
}

/*Completa o mapa com os enderecos referentes a rotulos e simbolos faltantes, emitindo uma mensagem de erro, caso eles 
nao tenham sido declarados posteriormente*/ 
void completa_mapa(rotulos *inicio_rotulos, sets *inicio_sets, mapa *mapa_memoria, int argc, FILE *arqs, FILE *arqe) {
    
    rotulos *rot;
    int i, j, k;
    
    for(i = 0; i < 1024; i++) {
        for(j = 0; j < 11; j++) {
            
            //Completa os enderecos de instrucoes
            if(mapa_memoria[i].palavra[j] == '-') {
                for(rot = inicio_rotulos; rot != NULL; rot = rot->prox) {
                    
                    //Caso o endereco a ser completado esteja do lado esquerdo
                    if(j <= 4) {
                        if((!strcmp(rot->nome_rotulo, mapa_memoria[i].rotulo_esq)) && (rot->rotulo_existente)) {
                            
                            char opcode[3];
                            
                            /*Verifica se ha a necessidade de modificar o opcode, para instrucoes que dependem do 
                            direcionamento do endereco*/
                            if(rot->pos_mont == 2) {
                                
                                for(k = 0; k < 2; k++) {
                                    opcode[k] = mapa_memoria[i].palavra[k];
                                }
                                opcode[2] = '\0';
                                
                                if(!strcmp(opcode, "0D")) {
                                    strcpy(opcode, "0E");
                                } 
                                else if(!strcmp(opcode, "0F")) {
                                    strcpy(opcode, "10");
                                } 
                                else if(!strcmp(opcode, "12")) {
                                    strcpy(opcode, "13");
                                }
                                
                                for(k = 0; k < 2; k++) {
                                    mapa_memoria[i].palavra[k] = opcode[k]; 
                                }
                            }
                            
                            //Completa o campo de endereco
                            for(k = 2; k < 5; k++) {
                                mapa_memoria[i].palavra[k] = rot->endereco[k - 2];
                            }
                            break;
                        }
                    }
                    //Caso o endereco a ser completado esteja do lado direito
                    else {
                        if((!strcmp(rot->nome_rotulo, mapa_memoria[i].rotulo_dir)) && (rot->rotulo_existente)) {
                            
                            char opcode[3];
                            
                            /*Verifica se ha a necessidade de modificar o opcode, para instrucoes que dependem do 
                            direcionamento do endereco*/
                            if(rot->pos_mont == 2) {
                                
                                for(k = 5; k < 7; k++) {
                                    opcode[k - 5] = mapa_memoria[i].palavra[k];
                                }
                                opcode[2] = '\0';
                                
                                if(!strcmp(opcode, "0D")) {
                                    strcpy(opcode, "0E");
                                } 
                                else if(!strcmp(opcode, "0F")) {
                                    strcpy(opcode, "10");
                                } 
                                else if(!strcmp(opcode, "12")) {
                                    strcpy(opcode, "13");
                                }
                                
                                for(k = 5; k < 7; k++) {
                                    mapa_memoria[i].palavra[k] = opcode[k - 5];
                                }
                            }
                            
                            //Completa o campo de endereco
                            for(k = 7; k < 10; k++) {
                                mapa_memoria[i].palavra[k] = rot->endereco[k - 7];
                            }
                            break;
                        }
                    }
                }
                
                if(!rot) {
                    imprime_erros(mapa_memoria[i].num_linha, "Rotulo nao declarado", "", argc, arqs, arqe, mapa_memoria, 
                                  inicio_rotulos, inicio_sets);
                }
            }
            //Completa os enderecos de .word e .wfill
            else if(mapa_memoria[i].palavra[j] == '+') {
                
                /*Percorre a lista de rotulos para verificar se a palavra foi declarada, emitindo mensagem de 
                erro caso nao consiga encontrar*/
                for(rot = inicio_rotulos; rot != NULL; rot = rot->prox) {
                    if((!strcmp(rot->nome_rotulo, mapa_memoria[i].rotulo_esq)) && (rot->rotulo_existente)) {
                        memset(mapa_memoria[i].palavra, '0', 10);
                        mapa_memoria[i].palavra[10] = '\0';
                        strcpy(&mapa_memoria[i].palavra[7], rot->endereco);
                        break;
                    }
                }
                
                if(rot == NULL) {
                    imprime_erros(mapa_memoria[i].num_linha, "Rotulo nao declarado", "", argc, arqs, arqe, mapa_memoria, 
                                  inicio_rotulos, inicio_sets);
                }
            }
        }
    }
}

//Desaloca as listas de rotulos alocadas
void desaloca_rotulos(rotulos *rot) {
    
    if(rot != NULL) {
        desaloca_rotulos(rot->prox);
    }
    free(rot);
}

//Desaloca as listas de sets alocadas
void desaloca_sets(sets *set) {
    
    if(set != NULL) {
        desaloca_sets(set->prox);
    }
    free(set);
}



