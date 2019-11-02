#include "conversoes.h"

//Retorna o opcode da instrucao, retornando "00", caso a instrucao nao exista
char *retorna_instrucao(char *instrucao) {
    
    if(!strcmp(instrucao, "LD")) {
        return "01";
    }
    else if(!strcmp(instrucao, "LD-")) {
        return "02";
    }
    else if(!strcmp(instrucao, "LD|")) {
        return "03";
    }
    else if(!strcmp(instrucao, "LDmq")) {
        return "0A";
    }
    else if(!strcmp(instrucao, "LDmq_mx")) {
        return "09";
    }
    else if(!strcmp(instrucao, "ST")) {
        return "21";
    }
    else if(!strcmp(instrucao, "JMP")) {
        return "0D0E";
    }
    else if(!strcmp(instrucao, "JUMP+")) {
        return "0F10";
    }
    else if(!strcmp(instrucao, "ADD")) {
        return "05";
    }
    else if(!strcmp(instrucao, "ADD|")) {
        return "07";
    }
    else if(!strcmp(instrucao, "SUB")) {
        return "06";
    }
    else if(!strcmp(instrucao, "SUB|")) {
        return "08";
    }
    else if(!strcmp(instrucao, "MUL")) {
        return "0B";
    }
    else if(!strcmp(instrucao, "DIV")) {
        return "0C";
    }
    else if(!strcmp(instrucao, "LSH")) {
        return "14";
    }
    else if(!strcmp(instrucao, "RSH")) {
        return "15";
    }
    else if(!strcmp(instrucao, "STaddr")) {
        return "1213";
    }
    
    return "00";
}   

//Dado um inteiro decimal, retorna uma string com o valor em hexadecimal
char *dec_para_hexa(long int decimal) {
    
    long int quociente, resto, i;
    char *hexa = (char *)malloc(11 * sizeof(char));
    memset(hexa, '0', 11);
    hexa[10] = '\0';
    
    i = 9;
    resto = decimal % 16;
    quociente = decimal / 16;
    
    if((resto >= 0) && (resto <= 9)) {
        hexa[i] = resto + '0';
    } else {
        hexa[i] = resto + 'A' - 10;
    }
    i--;
    while(quociente > 0) {
        
        resto = quociente % 16;
        quociente = quociente / 16;
        if((resto >= 0) && (resto <= 9)) {
            hexa[i] = resto + '0';
        } else {
            hexa[i] = resto + 'A' - 10;
        }
        
        i--;
    }
    
    return hexa;
}

//Dado uma string com um valor em hexadecimal, retorna um inteiro com o valor decimal
long int hexa_para_decimal(char *hexa) {
    
    long int dec = 0;
    int i, j;
    
    for(i = strlen(hexa) - 1, j = 0; i >= 0; i--, j++) {
        
        if((toupper(hexa[i]) >= 'A') && (toupper(hexa[i]) <= 'F')) {
            dec += (toupper(hexa[i]) - 'A' + 10) * potencia(j, 16);
        }
        else if((hexa[i] >= '0') && (hexa[i] <= '9')) {
            dec += (hexa[i] - '0') * potencia(j, 16);
        }
    }
    
    return dec;
}

//Dado uma string com um valor decimal, retorna um inteiro com o valor decimal correspondente
long int dec_para_dec(char *decimal) {
    
    long int dec = 0;
    int i, j;
    
    for(i = strlen(decimal) - 1, j = 0; i >= 0; i--, j++) {
        
        if((decimal[i] >= '0') && (decimal[i] <= '9')) {
            dec += (decimal[i] - '0') * potencia(j, 10);
        }
    }
    
    return dec;
}

//Calcula potencias de 10 e 16 para conversoes
long int potencia(int pow, int tipo) {
    
    int num = 1;
    
    for(int i = 0; i < pow; i++) {
        num *= tipo;    
    }
    return num;
}


