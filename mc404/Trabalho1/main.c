#include "verificacoes.h"
#include "impressoes.h"
#include "conversoes.h"
#include "operacoes-montador.h"

int main(int argc, char**argv) {
    
    FILE *arqe, *arqs;
    long int i, j;
    long int end_mapa = 0; //Armazena o endereco do mapa de memoria onde a palavra deve ser armazenada
    int num_linha = 1; //Armazena o numero da linha do arquivo de entrada
    int pos_mont = 1; //Variavel que define a posicao de montagem, sendo 1 = esquerda e 2 = direita
    char linha[4096]; //Vetor que armazena as linhas lidas do arquivo de entrada
    char linha_de_verificacao[4096]; /*Vetor que contem uma copia da linha lida do arquivo de entrada, para verificar 
                                     se a sintaxe da linha esta correta*/
    char *palavra; //Variavel que armazena cada palavra lida do arquivo de entrada
    char *hexa; //Variavel que armazena a string com o valor do numero em hexadecimal
    mapa *mapa_memoria; //Vetor que armazena o mapa de memoria
    rotulos *inicio_rotulos = NULL; //Lista que armazena os rotulos
    sets *inicio_sets = NULL; //Lista que armazena as diretivas .set
    
    mapa_memoria = malloc(1024 * sizeof(mapa));
    
    for(i = 0; i < 1024; i++){
        memset(mapa_memoria[i].palavra, '*', 10);
        memset(mapa_memoria[i].rotulo_esq, '0', 64);
        memset(mapa_memoria[i].rotulo_dir, '0', 64);
        memset(mapa_memoria[i].set, '0', 64);
        mapa_memoria[i].palavra[10] = '\0';
        mapa_memoria[i].rotulo_esq[64] = '\0';
        mapa_memoria[i].rotulo_dir[64] = '\0';
        mapa_memoria[i].set[64] = '\0';
    }
    
    /*Abre os arquivos de entrada e verifica se foram abertos corretamente*/
    arqe = fopen(argv[1], "r");
    if(argc == 3) {
        arqs = fopen(argv[2], "w");
    }
    if((arqe == NULL) && (arqs == NULL)) {
        //printf("Não foi possivel abrir o arquivo\n");
    }
    else {
        //printf("Arquivo aberto com sucesso\n");
    }
    
    
    //Realiza a leitura do arquivo de entrada
    while(fgets(linha, 4096, arqe)) {    
        
        //Variavel que indica se houve erro de sintaxe na linha
        int verifica_linha = 1;
        
        //Verifica se nao ha erro de sintaxe na linha 
        strcpy(linha_de_verificacao, linha);
        palavra = strtok(linha_de_verificacao, " \n\t");
        
        if(strcmp(linha, "\n")) {
            verifica_linha = verifica_sintaxe_linha(palavra, 0, num_linha, argc, arqs, arqe, mapa_memoria, 
                                                    inicio_rotulos, inicio_sets);
        }
        
        palavra = strtok(linha, " \n\t");
        
        if(verifica_linha) {
            
            while(palavra != NULL) {
                
                //Verifica se e um rotulo
                if(verifica_rotulo(palavra)) {
                    
                    rotulos *rot = verifica_rotulo_existente(inicio_rotulos, palavra);
                    
                    /*Verifica se o rotulo ja foi utilizado em alguma instrucao ou diretiva. Caso nao tenha sido 
                    utilizado, armazena-o na lista de rótulos. Caso ja tenha sido usado, apenas muda seu estado para 
                    existente*/
                    if(!rot) {
                        inicio_rotulos = insere_rotulos(palavra, inicio_rotulos, end_mapa, pos_mont, 1);
                    } else {
                        hexa = dec_para_hexa(end_mapa);
                        rot->rotulo_existente = 1;
                        strcpy(rot->endereco, &hexa[7]);
                        rot->end_mapa = end_mapa;
                        rot->pos_mont = pos_mont;
                        free(hexa);
                    }
                    
                }
                //Verifica se e uma diretiva
                else if(verifica_diretiva(palavra)) {
                    
                    int tipo_diretiva = verifica_diretiva(palavra);
                    
                    //Caso a diretiva seja um .set, armazena-a em uma lista
                    if(tipo_diretiva == 1) {
                        
                        char *simbolo = strtok(NULL, " \n\t");
                        char *valor_set = strtok(NULL, " \n\t");
                        
                        //Verifica se os argumentos subsequentes, sao um simbolo e um numero
                        if((simbolo != NULL) && (valor_set != NULL)) {
                            
                            //Verifica se o simbolo e uma palavra valida
                            if((simbolo != NULL) && (palavra_valida(simbolo))) {
                                
                                sets *set = verifica_set_existente(inicio_sets, simbolo);
                                
                                /*Verifica se o simbolo ja foi utilizado em alguma diretiva. Caso nao tenha sido 
                                utilizado, armazena-o na lista de .set. Caso ja tenha sido usado, emite uma mensagem 
                                de erro, pois foi declarado apos seu uso*/
                                if(!set) {
                                    
                                    //Verifica se o valor do .set e um decimal valido
                                    if(dec_valido(valor_set)) {
                                        hexa = dec_para_hexa(dec_para_dec(valor_set));
                                        inicio_sets =  insere_sets(simbolo, hexa, inicio_sets, 1);
                                        free(hexa);
                                    }
                                    //Verifica se o valor do .set e um hexadecimal valido
                                    else if(hexa_valido(valor_set)) {
                                        inicio_sets =  insere_sets(simbolo, &valor_set[2], inicio_sets, 1);
                                    } 
                                } else {
                                    
                                    for(int k = 0; k < 1023; k++) {
                                        
                                        if(!strcmp(mapa_memoria[k].set, set->simbolo)) {
                                            imprime_erros(mapa_memoria[k].num_linha, "Simbolo declarado posteiromente", 
                                                          "", argc, arqs, arqe, mapa_memoria, inicio_rotulos, 
                                                          inicio_sets);
                                        }
                                    }
                                }
                            } else {
                                imprime_erros(num_linha, " nao e um argumento valido", valor_set, argc, arqs, arqe, 
                                              mapa_memoria, inicio_rotulos, inicio_sets);
                            }
                        } else {
                            imprime_erros(num_linha, "Falta Argumento", "", argc, arqs, arqe, mapa_memoria, 
                                          inicio_rotulos, inicio_sets);
                        }
                    }
                    //Caso seja um .org
                    else if(tipo_diretiva == 2) {
                        
                        palavra = strtok(NULL, " \n\t");
                        
                        //Verifica se o argumento existe e e valido
                        if(palavra != NULL) {
                            
                            //Verifica se o argumento e um hexadecimal valido
                            if(hexa_valido(palavra)) {
                                
                                end_mapa = hexa_para_decimal(palavra);
                                
                                if(end_mapa > 1023) {
                                    imprime_erros(num_linha, "Acesso a posicao invalida de memoria", "", argc, arqs, 
                                                  arqe, mapa_memoria, inicio_rotulos, inicio_sets);
                                }
                            }
                            //Verifica se e um decimal valido
                            else if(dec_valido(palavra)) {
                                
                                end_mapa = dec_para_dec(palavra);
                                
                                if(end_mapa > 1023) {
                                    imprime_erros(num_linha, "Acesso a posicao invalida de memoria", "", argc, arqs, 
                                                  arqe, mapa_memoria, inicio_rotulos, inicio_sets);
                                }
                            } else {
                                imprime_erros(num_linha, " nao e um argumento valido", palavra, argc, arqs, arqe, 
                                              mapa_memoria, inicio_rotulos, inicio_sets);
                            }
                        } else {
                            imprime_erros(num_linha, "Falta argumento", "", argc, arqs, arqe, mapa_memoria, 
                                          inicio_rotulos, inicio_sets);
                        }
                        
                        /*Caso a posicao de montagem esteja do lado direito quando ocorrer o .org, muda-a para o lado 
                        esquerdo*/
                        if(pos_mont == 2) {
                            pos_mont = 1;
                        }
                    }
                    //Caso seja um .align
                    else if(tipo_diretiva == 3) {
                        
                        palavra = strtok(NULL, " \n\t");
                        
                        int align;
                        
                        //Veririfica se o simbolo existe
                        if(palavra != NULL) {
                            
                            //Verifica se o argumento e um decimal valido
                            if(dec_valido(palavra)) {
                                
                                align = dec_para_dec(palavra);
                                
                                //Verifica se a montagem se encontra a direita
                                if(pos_mont == 2) {
                                    pos_mont = 1;
                                    if(end_mapa < 1023) {
                                        end_mapa++;
                                    }
                                }
                                
                                //Realiza o align se nao ultrapassar o maximo de linhas
                                if(end_mapa <= 1023) {
                                    
                                    while((end_mapa % align) && (end_mapa < 1023)) {
                                        end_mapa++;
                                    }
                                } else {
                                    imprime_erros(num_linha, "Acesso a posicao invalida de memoria", "", argc, arqs, 
                                                  arqe, mapa_memoria, inicio_rotulos, inicio_sets);
                                }
                            } else {
                                imprime_erros(num_linha, " nao e um argumento valido", palavra, argc, arqs, arqe, 
                                              mapa_memoria, inicio_rotulos, inicio_sets);
                            }
                        } else {
                            imprime_erros(num_linha, "Falta argumento", "", argc, arqs, arqe, mapa_memoria, 
                                          inicio_rotulos, inicio_sets);
                        }
                    }
                    //Caso a diretiva seja um .wfill
                    else if(tipo_diretiva == 4) {
                        
                        palavra = strtok(NULL, " \n\t");
                        
                        //Verifica se o argumento existe e se e um decimal valido
                        if((palavra != NULL) && (dec_valido(palavra))) {
                            
                            int nwfill = dec_para_dec(palavra); //Armazena o numero de linhas que serao utilizadas
                            int id_encontrado = 0;/*Variavel que identifica se o simbolo ou rotulo utilizado como 
                            argumento, ja foi utilizado*/
                            
                            palavra = strtok(NULL, " \n\t");
                            
                            //Caso a posicao de montagem estiver do lado direito
                            if(pos_mont == 2) {
                                imprime_erros(num_linha, "Posicao de montagem se encontra do lado direito", "", argc, 
                                              arqs, arqe, mapa_memoria, inicio_rotulos, inicio_sets);
                            }
                            
                            //Caso ele tente colocar quantidade de posicoes, fora do intervalo [1:1023]
                            if((nwfill == 0) || (nwfill > 1023)) {
                                imprime_erros(num_linha, "Acesso a posicao invalida de memoria", "", argc, arqs, arqe, 
                                              mapa_memoria, inicio_rotulos, inicio_sets);
                            }
                            
                            //Verifica se o valor a ser adicionado e um hexadecimal
                            if(hexa_valido(palavra)) {
                                id_encontrado = 1;
                            }
                            //Verifica se o valor a ser adicionado e um decimal
                            else if(dec_valido(palavra)) {
                                hexa = dec_para_hexa(dec_para_dec(palavra));
                                strcpy(palavra, hexa);
                                free(hexa);
                                id_encontrado = 1;
                            } 
                            //Verifica se o valor a ser adicionado e um simbolo ou rotulo
                            else if(palavra_valida(palavra)) {
                                
                                rotulos *rot;
                                sets *set;
                                
                                //Percorre as listas de rotulos e .set procurando a palavra utilizada como argumento
                                for(rot = inicio_rotulos; (rot != NULL) && (!id_encontrado); rot = rot->prox) {
                                    if(!strcmp(rot->nome_rotulo, palavra)) {
                                        strcpy(palavra, rot->endereco);
                                        id_encontrado = 1;
                                    }
                                }
                                
                                for(set = inicio_sets; (set != NULL) && (!id_encontrado); set = set->prox) {
                                    if(!strcmp(set->simbolo, palavra)) {
                                        strcpy(palavra, set->valor);
                                        id_encontrado = 1;
                                    }
                                }
                            }
                            
                            //Adiciona os valores correspondentes
                            if((end_mapa + nwfill) <= 1024) {
                                
                                //Caso o argumento tenha sido encontrado
                                if((id_encontrado)) {
                                    for(i = end_mapa, j = 0; j < nwfill; i++, j++) {
                                        memset(mapa_memoria[i].palavra, '0', 10);
                                        adiciona_palavras(palavra, mapa_memoria, i);
                                    }
                                }
                                /*Caso o simbolo ou rotulo nao tenha sido encontrado, armazena a palavra para posterior 
                                verificacao*/
                                else { 
                                    
                                    /*Armazena o argumento tanto na lista de rotulos como na de .set para posterior 
                                    verificacao*/
                                    inicio_sets =  insere_sets(palavra, "000\0", inicio_sets, 0);
                                    inicio_rotulos = insere_rotulos(palavra, inicio_rotulos, end_mapa, pos_mont, 0);
                                    
                                    /*Armazena nas posicoes especificadas o caractere especial '+', para que depois 
                                    seja substituido pelos valores corretos, caso o rotulo ou simbolo tenha sido 
                                    declarado posteiromente*/
                                    for(i = end_mapa, j = 0; j < nwfill; i++, j++) {
                                        memset(mapa_memoria[i].palavra, '+', 10);
                                        strcpy(mapa_memoria[i].rotulo_esq, palavra);
                                        strcpy(mapa_memoria[i].rotulo_dir, palavra);
                                        strcpy(mapa_memoria[i].set, palavra);
                                    }
                                }
                                
                                end_mapa += nwfill;
                                
                            } else {
                                imprime_erros(num_linha, "Acesso a posicao invalida de memoria", "", argc, arqs, arqe, 
                                              mapa_memoria, inicio_rotulos, inicio_sets);
                            }
                        } else {
                            imprime_erros(num_linha, " nao e um argumento valido", palavra, argc, arqs, arqe, 
                                          mapa_memoria, inicio_rotulos, inicio_sets);
                        }
                    }
                    //Caso a diretiva seja um .word
                    else if(tipo_diretiva == 5) {
                        
                        palavra = strtok(NULL, " \n\t");
                        
                        //Verifica se o identificador de escrita esta a esquerda. Caso contrario, emite um erro
                        if(pos_mont == 1) {
                            
                            //Verifica se a palavra seguinte e um hexadecimal valido
                            if(hexa_valido(palavra)) {
                                memset(mapa_memoria[end_mapa].palavra, '0', 10);
                                adiciona_palavras(palavra, mapa_memoria, end_mapa);
                            }
                            //Verifica se a palavra seguinte e um decimal valido
                            else if(dec_valido(palavra)) {
                                memset(mapa_memoria[end_mapa].palavra, '0', 10);
                                hexa = dec_para_hexa(dec_para_dec(palavra));
                                adiciona_palavras(hexa, mapa_memoria, end_mapa);
                                free(hexa);
                            }
                            //Verifica se a palavra seguinte e um rotulo ou simbolo
                            else if(palavra_valida(palavra)) {
                                
                                rotulos *rot;
                                sets *set;
                                int id_encontrado = 0; /*Variavel que identifica se o simbolo ou rotulo utilizado como 
                                argumento, ja foi utilizado*/
                                
                                memset(mapa_memoria[end_mapa].palavra, '0', 10);
                                
                                //Percorre as listas de rotulos e .set procurando a palavra utilizada como argumento
                                for(rot = inicio_rotulos; (rot != NULL) && (!id_encontrado); rot = rot->prox) {
                                    if(!strcmp(rot->nome_rotulo, palavra)) {
                                        adiciona_palavras(rot->endereco, mapa_memoria, end_mapa);
                                        id_encontrado = 1;
                                    }
                                }
                                
                                for(set = inicio_sets; (set != NULL) && (!id_encontrado); set = set->prox) {
                                    if(!strcmp(set->simbolo, palavra)) {
                                        adiciona_palavras(set->valor, mapa_memoria, end_mapa);
                                        id_encontrado = 1;
                                    }
                                }
                                
                                /*Caso o simbolo ou rotulo nao tenha sido encontrado nas listas de rotulos e sets, 
                                armazena o argumento tanto na lista de rotulos quanto na lista de .set para 
                                posterior verificacao*/
                                if(!id_encontrado) {
                                    inicio_rotulos = insere_rotulos(palavra, inicio_rotulos, end_mapa, pos_mont, 0);
                                    inicio_sets =  insere_sets(palavra, "0000000000", inicio_sets, 0);
                                    memset(mapa_memoria[end_mapa].palavra, '+', 10);
                                    strcpy(mapa_memoria[end_mapa].rotulo_esq, palavra);
                                    strcpy(mapa_memoria[end_mapa].rotulo_dir, palavra);
                                    strcpy(mapa_memoria[end_mapa].set, palavra);
                                    mapa_memoria[end_mapa].num_linha = num_linha;
                                }
                            }
                            
                            if(end_mapa < 1023) {
                                end_mapa++;
                            }
                        } else {
                            imprime_erros(num_linha, "Posicao de montagem se encontra do lado direito", "", argc, arqs, 
                                          arqe, mapa_memoria, inicio_rotulos, inicio_sets);
                        }
                    }
                }
                //Verifica se e uma instrucao
                else if(strcmp(retorna_instrucao(palavra), "00")) {
                    
                    char *opcode = retorna_instrucao(palavra); //Variavel que armazena o opcode da instrucao
                    
                    //Caso nao precise de um endereco, apenas armazena o opcode da instrucao
                    if(!(strcmp(opcode, "0A")) || !(strcmp(opcode, "14")) || !(strcmp(opcode, "15"))) {
                        adiciona_instrucao(opcode, "000", mapa_memoria, end_mapa, pos_mont);
                    }
                    
                    palavra = strtok(NULL, " \n");
                    
                    //Verifica se ela esta entre aspas como especificado
                    if((palavra != NULL) && (palavra[0] == '\"') && (palavra[strlen(palavra) - 1]) == '\"') {
                        
                        //Retira as aspas do endereco da instrucao
                        for(i = 0; i < strlen(palavra); i++) {
                            palavra[i] = palavra[i + 1];
                        }
                        palavra[strlen(palavra) - 1] = '\0';
                        
                        //Verifica se o endereco e um hexadecimal valido
                        if(hexa_valido(palavra)) {
                            
                            for(i = 0; i < strlen(palavra); i++) {
                                palavra[i] = toupper(palavra[i]);
                            }
                            adiciona_instrucao(opcode, &palavra[9], mapa_memoria, end_mapa, pos_mont);
                        }
                        //Verifica se o endereco e um decimal valido
                        else if(dec_valido(palavra)) {
                            
                            hexa = dec_para_hexa(dec_para_dec(palavra));
                            adiciona_instrucao(opcode, &hexa[7], mapa_memoria, end_mapa, pos_mont);
                            free(hexa);
                        }
                        //Verifica se e uma palavra palavra valida
                        else if(palavra_valida(palavra)) {
                            
                            rotulos *rot = verifica_rotulo_existente(inicio_rotulos, palavra);
                            
                            //Verifica se e um rotulo existente
                            if(rot) {
                                
                                /*Verifica se a instrucao e um salto ou armazenamento que possui opcodes diferentes 
                                para caso sejam para a esquerda ou direita*/
                                if((!strcmp(opcode, "0D0E")) || (!strcmp(opcode, "0F10")) || (!strcmp(opcode,"1213"))){
                                    
                                    //Caso seja uma instrucao direcionada para a esquerda
                                    if(rot->pos_mont == 1) {
                                        
                                        /*Caso o armazenamento nao tenha sido realizado com sucesso, emite mensagem de 
                                        erro*/
                                        if(!adiciona_instrucao(opcode, rot->endereco, mapa_memoria, end_mapa,pos_mont)){
                                            imprime_erros(num_linha, "Lado esquerdo da palavra de memoria, vazio", "", 
                                                          argc, arqs, arqe, mapa_memoria, inicio_rotulos, inicio_sets);
                                        }
                                    }
                                    //Caso seja uma instrucao direcionada para a direita
                                    else if(rot->pos_mont == 2) {
                                        
                                        /*Caso o armazenamento nao tenha sido realizado com sucesso, emite mensagem de 
                                        erro*/
                                        if(!adiciona_instrucao(&opcode[2],rot->endereco,mapa_memoria, end_mapa, 
                                                               pos_mont)){
                                            imprime_erros(num_linha, "Lado esquerdo da palavra de memoria, vazio", "", 
                                                          argc, arqs, arqe, mapa_memoria, inicio_rotulos, inicio_sets);
                                        }
                                    }   
                                } 
                                //Caso seja uma instrucao que nao depende do direcionamento para obter o opcode
                                else {
                                    /*Caso o armazenamento nao tenha sido realizado com sucesso, emite mensagem de 
                                    erro*/
                                    if(!adiciona_instrucao(opcode, rot->endereco, mapa_memoria, end_mapa, pos_mont)) {
                                       imprime_erros(num_linha, "Lado esquerdo da palavra de memoria, vazio", "", argc, 
                                                     arqs, arqe, mapa_memoria, inicio_rotulos, inicio_sets);
                                    }    
                                }
                            }
                            /*Caso o simbolo ou rotulo nao tenha sido utilizado ainda, preenche a linha do mapa de 
                            montagem com o opcode correspondente a instrucao e com o caractere especial '-' no lugar do 
                            endereco para posterior verificacao*/
                            else {
                                if(!adiciona_instrucao(opcode, "---", mapa_memoria, end_mapa, pos_mont)) {
                                    imprime_erros(num_linha, "Lado esquerdo da palavra de memoria, vazio", "", argc, 
                                                  arqs, arqe, mapa_memoria, inicio_rotulos, inicio_sets);
                                }
                                
                                if(pos_mont == 1) {
                                    strcpy(mapa_memoria[end_mapa].rotulo_esq, palavra);
                                } else {
                                    strcpy(mapa_memoria[end_mapa].rotulo_dir, palavra);
                                }
                                mapa_memoria[end_mapa].num_linha = num_linha;
                                inicio_rotulos = insere_rotulos(palavra, inicio_rotulos, end_mapa, pos_mont, 0);
                            }  
                        }
                    }
                    //Modifica o identificador para direita ou esquerda, de acordo com a posicao atual
                    if(pos_mont == 1) {
                        pos_mont = 2;
                    } else {
                        pos_mont = 1;
                        if(end_mapa < 1023) {
                            end_mapa++;
                        }
                    }
                }
                //Veririfica se a palavra lida e um comentario
                else if(verifica_comentario(palavra)) {
                    while(palavra != NULL) {
                        palavra = strtok(NULL, " \n\t");
                    }
                }
                
                palavra = strtok(NULL, " \n\t");
            }
        } 
        
        num_linha++;
    }
    
    //Completa os enderecos faltantes 
    completa_mapa(inicio_rotulos, inicio_sets, mapa_memoria, argc, arqs, arqe);
    
    //Completa com zeros, as posicoes de memoria que nao foram preenchidas
    for(i = 0; i < 1024; i++, j = 0) {
        if(mapa_memoria[i].palavra[0] != '*') {
            for(j = 0; j < 10; j++) {
                if(mapa_memoria[i].palavra[j] == '*') {
                    mapa_memoria[i].palavra[j] = '0';
                }
            }
        }
    }

    imprime_mapa(mapa_memoria, argc, arqs);
    
    free(mapa_memoria);
    
    desaloca_rotulos(inicio_rotulos);
    desaloca_sets(inicio_sets);
    
    fclose(arqe);
    if(argc == 3){
        fclose(arqs);
    }
    
    return 0;
}

