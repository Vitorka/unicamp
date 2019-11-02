#include "verificacoes.h"

//Verifica se o endereco fornecido e um hexadecimal valido
int hexa_valido(char *hexa) {
    
    int i;
    
    //Verifica se e um numero formado apenas por caracteres hexadecimais
    if(strlen(hexa) == 12) {
        if((hexa[0] == '0') && (hexa[1] == 'x')) {
            for(i = 2; i < strlen(hexa); i++) {
                if(!isxdigit(hexa[i])) {
                    return 0;
                }
            }
            
            return 1;
        }
    }
    
    return 0;
}

//Verifica se o endereco e um decimal valido
int dec_valido(char *dec) {
    
    int i;
    
    //Verifica se e um numero formado apenas por caracteres decimais
    for(i = 0; i < strlen(dec); i++) {
        
        if(!isdigit(dec[i])) {
            return 0;
        }
    }
    
    return 1;
}

//Verifica se e um rotulo ou simbolo valido
int palavra_valida(char *palavra) {
    
    int i;
    
    //Verifica se nao comeca com um numero
    if(isdigit(palavra[0])) {
        return 0;
    }
    
    //Verifica se e formado apenas por caracteres alfanumericos ou underscores
    for(i = 0; i < strlen(palavra); i++) {
        
        if((!isalnum(palavra[i])) && (palavra[i] != '_')) {
            return 0;
        }
    }
    
    return 1;
}


//Veririfica se e um rotulo
int verifica_rotulo(char *rotulo) {
    
    //Verifica se possui o caractere ":" no final
    if(rotulo[strlen(rotulo) - 1] != ':') {
        return 0;
    }
        
    rotulo[strlen(rotulo) - 1] = '\0';
    
    return palavra_valida(rotulo);
}

/*Verifica se e uma diretiva. Caso retorne 1, indica uma diretiva .set; caso 
retorne 2, indica uma diretiva .org; caso retorne 3, indica uma diretiva .align; caso retorne 4, 
indica uma diretiva .wfill; caso retorne 5, indica uma diretiva .word; caso retorne 0, indica que 
um erro ocorreu*/
int verifica_diretiva(char *diretiva) {
    
    if(diretiva[0] == '.') {
        
        if(!strcmp(diretiva, ".set")) {
            return 1;
        }
        else if(!strcmp(diretiva, ".org")) {
            return 2;
        }
        else if(!strcmp(diretiva, ".align")) {
            return 3;
        }
        else if(!strcmp(diretiva, ".wfill")) {
            return 4;
        }
        else if(!strcmp(diretiva, ".word")) {
            return 5;
        }
    }
    
    return 0;
}

/*Funcao que verifica se ha erro de sintaxe na linha. A variavel id representa a tipo de argumento que sera analisado. 
Caso seja 0, representa que e a primeira analise; caso seja 1, representa que o argumento analisado e um rotulo; caso 
seja 2, representa que o argumento analisado e uma diretiva; caso seja 3, representa que o argumento analisado e uma 
instrucao; caso seja 4, representa que o argumento analisado e um comentario*/
int verifica_sintaxe_linha(char *palavra, int id, int num_linha, int argc, FILE *arqs, FILE *arqe, 
                           mapa *mapa_memoria, rotulos *inicio_rotulos, sets *inicio_sets) {
    
    //Realiza a primeira analise
    if((palavra != NULL) && (id == 0)) {
        
        if(verifica_rotulo(palavra)) {
            return verifica_sintaxe_linha(palavra, 1, num_linha, argc, arqs, arqe, mapa_memoria, inicio_rotulos, 
                                          inicio_sets);
        } 
        else if(verifica_diretiva(palavra)) {
            return verifica_sintaxe_linha(palavra, 2, num_linha, argc, arqs, arqe, mapa_memoria, inicio_rotulos, 
                                          inicio_sets);
        }
        else if(strcmp(retorna_instrucao(palavra), "00")) {
            return verifica_sintaxe_linha(palavra, 3, num_linha, argc, arqs, arqe, mapa_memoria, inicio_rotulos, 
                                          inicio_sets);
        }
        else if(verifica_comentario(palavra)) {
            return 1;
        } else {
            imprime_erros(num_linha, " nao e um mnemonico valido", palavra, argc, arqs, arqe, mapa_memoria, 
                          inicio_rotulos, inicio_sets);
        }
    }
    //Caso seja um rotulo, verifica se depois dele, vem um rotulo, ou uma diretiva ou um comentario
    else if((palavra != NULL) && (id == 1)) {
        
        palavra = strtok(NULL, " \n\t");
        
        if((palavra != NULL) && (verifica_diretiva(palavra))) {
            return verifica_sintaxe_linha(palavra, 2, num_linha, argc, arqs, arqe, mapa_memoria, inicio_rotulos, 
                                          inicio_sets);
        }
        else if((palavra != NULL) && (strcmp(retorna_instrucao(palavra), "00"))) {
            return verifica_sintaxe_linha(palavra, 3, num_linha, argc, arqs, arqe, mapa_memoria, inicio_rotulos, 
                                          inicio_sets);
        } 
        else if((palavra != NULL) && (verifica_comentario(palavra))) {
            return verifica_sintaxe_linha(palavra, 4, num_linha, argc, arqs, arqe, mapa_memoria, inicio_rotulos, 
                                          inicio_sets);
        } 
        else if(palavra == NULL){
            return 1;
        } else {
            return verifica_sintaxe_linha(palavra, 4, num_linha, argc, arqs, arqe, mapa_memoria, inicio_rotulos, 
                                          inicio_sets);
        }
    }
    /*Caso seja uma diretiva, verifica se os argumentos esperados por cada uma delas sao validos e que nao exista mais 
    nada na linha a nao ser comentarios*/
    else if((palavra != NULL) && (id == 2)) {
        int diretiva = verifica_diretiva(palavra);
        
        palavra = strtok(NULL, " \n\t");
        
        /*Caso a diretiva seja um .org ou .align ou .word, verifica se a proxima palavra corresponde ao argumento 
        esperado, ou seja, um hexadecimal, ou um decimal ou um simbolo ou rotulo*/
        if((palavra != NULL) && ((diretiva == 2) || (diretiva == 3) || (diretiva == 5))) {
            
            if((palavra != NULL) && ((hexa_valido(palavra)) || (dec_valido(palavra)) || (palavra_valida(palavra)))) {
                palavra = strtok(NULL, " \n\t");
                return verifica_sintaxe_linha(palavra, 4, num_linha, argc, arqs, arqe, mapa_memoria, inicio_rotulos, 
                                              inicio_sets);
            } else {
                
                if(palavra != NULL) {
                    imprime_erros(num_linha, " nao e um argumento valido", palavra, argc, arqs, arqe, mapa_memoria, 
                                  inicio_rotulos, inicio_sets);
                } else {
                    imprime_erros(num_linha, "Falta argumento", "", argc, arqs, arqe, mapa_memoria, inicio_rotulos, 
                                  inicio_sets);
                }
            }
        }
        /*Caso a diretiva seja um .set ou .wfill, verifica se as proximas palavras correspondem aos argumentos 
        esperados, ou seja, um simbolo e um hexadecimal ou decimal, apos o .set, ou um decimal e um hexadecimal, ou 
        decimal, ou simbolo, ou rotulo, apos o .wfill*/
        else if((palavra != NULL) && ((diretiva == 1) || (diretiva == 4))) {
            
            //Verifica se a palavra seguinte e um simbolo valido, ou um hexadecimal ou um decimal
            if((palavra != NULL) && ((palavra_valida(palavra)) || (hexa_valido(palavra)) || (dec_valido(palavra)))) {
                
                palavra = strtok(NULL, " \n\t");
                
                //Verifica se a palavra seguinte e um hexadecimal, ou um decimal, ou uma palavra
                if((palavra != NULL) && ((hexa_valido(palavra)) || (dec_valido(palavra)) || 
                   (palavra_valida(palavra)))) {
                    palavra = strtok(NULL, " \n\t");
                    return verifica_sintaxe_linha(palavra, 4, num_linha, argc, arqs, arqe, mapa_memoria, 
                                                  inicio_rotulos, inicio_sets);
                } else {
                    
                    if(palavra != NULL) {
                        imprime_erros(num_linha, " nao e um argumento valido", palavra, argc, arqs, arqe, mapa_memoria, 
                                      inicio_rotulos, inicio_sets);
                    } else {
                        imprime_erros(num_linha, "Falta argumento", "", argc, arqs, arqe, mapa_memoria, inicio_rotulos, 
                                      inicio_sets);
                    }
                }
            } else {
                
                if(palavra != NULL) {
                    imprime_erros(num_linha, " e um argumento invalido", palavra, argc, arqs, arqe, mapa_memoria, 
                                  inicio_rotulos, inicio_sets);
                } else {
                    imprime_erros(num_linha, "Falta argumento", "", argc, arqs, arqe, mapa_memoria, inicio_rotulos, 
                                  inicio_sets);
                }
                
            }
        } else {
            imprime_erros(num_linha, "Falta argumento", "", argc, arqs, arqe, mapa_memoria, inicio_rotulos, 
                          inicio_sets);
        }
    }
    /*Caso seja uma instrucao, verifica, nos casos que necessitam de argumento, se ele e um decimal, ou hexadecimal, 
    ou um rotulo*/
    else if(id == 3) {
        
        char *instrucao = retorna_instrucao(palavra);
        
        //Verifica se sao instrucoes que nao precisa de argumento
        if(!(strcmp(instrucao, "0A")) || !(strcmp(instrucao, "14")) || !(strcmp(instrucao, "15"))) {
            palavra = strtok(NULL, " \n\t");
            return  verifica_sintaxe_linha(palavra, 4, num_linha, argc, arqs, arqe, mapa_memoria, inicio_rotulos, 
                                           inicio_sets);
        } else {
            palavra = strtok(NULL, " \n\t");
            
            //Verifica se o argumento esta entre aspas como esperado
            if((palavra != NULL) && (palavra[0] == '\"') && (palavra[strlen(palavra) - 1] == '\"')) {
                for(int i = 0; i < strlen(palavra); i++) {
                    palavra[i] = palavra[i + 1];
                }
                palavra[strlen(palavra) - 1] = '\0';
                
                if((dec_valido(palavra)) || (hexa_valido(palavra)) || (palavra_valida(palavra))) {
                    palavra = strtok(NULL, " \n\t");
                    return verifica_sintaxe_linha(palavra, 4, num_linha, argc, arqs, arqe, mapa_memoria, 
                                                  inicio_rotulos, inicio_sets);
                } else {
                    imprime_erros(num_linha, " nao e um argumento valido", palavra, argc, arqs, arqe, mapa_memoria, 
                                  inicio_rotulos, inicio_sets);
                }
            } else {
                if(palavra != NULL) {
                    imprime_erros(num_linha, "Endereco nao contem aspas", "", argc, arqs, arqe, mapa_memoria, 
                                  inicio_rotulos, inicio_sets);
                } else {
                    imprime_erros(num_linha, "Falta argumento", "", argc, arqs, arqe, mapa_memoria, inicio_rotulos, 
                                  inicio_sets);
                }
            }
        }
    }
    //Caso seja um comentario
    else if(id == 4) {
        
        if((palavra != NULL) && (verifica_comentario(palavra))) {
            return 1;
        } 
        else if(palavra == NULL) {
            return 1;
        } else {
            imprime_erros(num_linha, "Argumentos a mais na linha", "", argc, arqs, arqe, mapa_memoria, inicio_rotulos, 
                          inicio_sets);
        }
    }    
    return 1;
}

//Verifica se o rotulo existe na lista de rotulos
rotulos *verifica_rotulo_existente(rotulos *inicio_rotulos, char *palavra) {
    
    rotulos *rot;
    
    if(inicio_rotulos) {
        for(rot = inicio_rotulos; rot; rot = rot->prox) {
            if(!strcmp(rot->nome_rotulo, palavra)) {
                return rot;
            }
        }
    }
    return NULL;
} 

//Verifica se o .set existe na lista de .set
sets *verifica_set_existente(sets *inicio_sets, char *palavra) {
    
    sets *set;
    
    if(inicio_sets != NULL) {
        for(set = inicio_sets; set; set = set->prox) {
            if(!strcmp(set->simbolo, palavra)) {
                return set;
            }
        }
    }
    return NULL;
}


//Veririfica se e um comentario
int verifica_comentario(char *comentario) {
    
    if(comentario[0] == '#') {
        return 1;
    }
    
    return 0;
}
