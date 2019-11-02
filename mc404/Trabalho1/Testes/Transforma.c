#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef struct teste {
    int i;
    char vitor[3];
} test;


long int potencia(int pow, int tipo) {
    
    long int num = 1;
    
    for(int i = 0; i < pow; i++) {
        num *= tipo;    
    }
    return num;
}

int dec_para_dec(char *teste) {
    
    int dec = 0;
    int i, j;
    //printf("%s\n", teste);
    for(i = strlen(teste) - 1, j = 0; i >= 0; i--, j++) {
        printf("%c\n", teste[i]);
        if((teste[i] >= '0') && (teste[i] <= '9')) {
            dec += (teste[i] - '0') * potencia(j, 10);
        }
    }
    
    return dec;
}

long hexa_para_decimal(char *teste) {
    
    long int dec = 0;
    int i, j;
    
    for(i = strlen(teste) - 1, j = 0; i >= 0; i--, j++) {
        
        if((toupper(teste[i]) >= 'A') && (toupper(teste[i]) <= 'F')) {
            dec += (toupper(teste[i]) - 'A' + 10) * potencia(j, 16);
        }
        else if((teste[i] >= '0') && (teste[i] <= '9')) {
            dec += (teste[i] - '0') * potencia(j, 16);
        }
        printf("dec: %ld\n", dec);
    }
    
    return dec;
}

char *dec_para_hexa(long int decimal) {
    int quociente, resto, i;
    char *hexa = (char *)malloc(11 * sizeof(char));
    memset(hexa, '0', 11);
    
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

int endereco_hexa(char *endereco) {
    
    int i;
    int valor_decimal;
    
    //Verifica se eh um valor hexadecimal
    if(strlen(endereco) == 12) {
        if((endereco[0] == '0') && (endereco[1] == 'x')) {
            for(i = 2; i < strlen(endereco); i++) {
                if(!isxdigit(endereco[i])) {
                    return 0;
                }
            }
            //Verifica se o endereco esta no intervalo [0;1023]
            valor_decimal = hexa_para_decimal(&endereco[2]);
            if((valor_decimal < 0) || (valor_decimal > 1023)) {
                return 0;
            }
        
            return 1;
        }
    }
    
    return 0;
}

int endereco_dec(char *endereco) {
    
    int i;
    int valor_decimal;
    
    //Verifica se o endereco dado eh um numero negativo
    if(endereco[0] == '-') {
        return 0;
    }
    
    //Verifica se o endereco eh formado apenas por numeros
    for(i = 0; i < strlen(endereco); i++) {
        
        if(!isdigit(endereco[i])) {
            return 0;
        }
    }
    
    //Verifica se o numero esta no intervalo [0;1023]
    valor_decimal = dec_para_dec(endereco);
    if((valor_decimal < 0) || (valor_decimal > 1023)) {
        return 0;
    }
    
    return 1;
}

int endereco_rot(char *endereco) {
    
    int i;
    
    printf("%s\n", endereco);
    
    //Verifica se nao comeca com um numero
    if(isdigit(endereco[0])) {
        return 0;
    }
    
    //Verifica se eh formado apenas por caracteres alfanumericos ou underscores
    for(i = 0; i < strlen(endereco); i++) {
        
        if((!isalnum(endereco[i])) && (endereco[i] != '_')) {
            return 0;
        }
    }
    
    return 1;
}

void muda_int(int *i) {
    *i = 1;
}

int main(){
    //char teste[65] = "teste para saber se vai dar certo";
    //char teste2[11] = "Teste ";
    //test *aux = malloc(2 * sizeof(test));
    //char hexa[3];
    //long decimal;
    //char *hexa;
    //char *e;
    int i = 0;
    
    muda_int(&i);
    printf("%d\n", i);
    
    
    
    //sprintf(teste2, "%ld", FFFFFFFFFF);
    //hexa = dec_para_hexa(34849038903824 );
    
    //printf("%s\n", teste2);
    //printf("%s\n", hexa);
    
    /*for(int i = 0; i < 2; i++) {
            strcpy(aux[i].vitor, "001");
        
    }
    
    for(int i = 0; i < 2; i++) {
            printf("%s\n", aux[i].vitor);
        
        
    }*/
    
    //strcpy(teste2, teste);
    //printf("teste = %s\n", teste);
    //printf("teste2 = %s\n", teste2);
    /*hexa = strtok(teste, " ");
    
    while(hexa != NULL) {
        printf("%s\n", hexa);
        hexa = strtok(NULL, " ");
    }
    
    printf("\n2:\n");
    hexa = strtok(teste2, " ");
    while(hexa != NULL) {
        printf("%s\n", hexa);
        hexa = strtok(NULL, " ");
    }*/
    
    
    /*for(i = 0; i < strlen(teste2); i++) {
        teste2[i] = teste2[i + 1];
    }
    
    printf("%ld\n", strlen(teste2));
    teste2[strlen(teste2) - 1] = '\0';
    printf("%ld\n", strlen(teste2));
    printf("%s\n", teste2);*/

    
    /*sprintf(teste, "%010X", -10);
    printf("%s\n", teste);
    sprintf(teste2, "%ld", teste);
    printf("%s\n", teste2);
    
    printf("")*/
    
    //printf("%c%c %c%c%c %c%c %c%c%c\n", teste);
    
    
    /*scanf("%s", teste);
    teste[strlen(teste) - 1] = '\0';
    if(!endereco_rot(teste)) {
        printf("ok\n");
    } else {
        printf("eh uma palavra\n");
    }*/
    
    /*if(endereco_dec(teste2) == 0) {
        printf("ok\n");
    } else {
        printf("eh um numero valido\n");
    }*/
    
    /*if((teste[0] == '\"') && (teste[strlen(teste) - 1] == '\"')) {
        for(i = 1, j = 0; i < strlen(teste) - 1; i++, j++) {
            teste2[j] = teste[i];
        }
    }
    
    if(endereco_hexa(teste2) == 1) {
        printf("ok\n");
    }*/
    
    
    //hexa = strtok(teste, " \"");
    
    /*for(int i = 0; i < strlen(teste); i++) {
        
        if(isxdigit(teste[i])) {
            printf("%c", teste[i]);
        }
    }
    printf("\n");*/
    
    
   /* while(hexa != NULL) {
        printf("%s\n", hexa);
        hexa = strtok(NULL, " \"");
    }*/
    
    //printf("%s", hexa);
   
    /*while(hexa != NULL) {
        while(e != NULL) {
            e = strtok(hexa, ": ");
            printf("%s\n", e);
            e = strtok(NULL, ": ");
        }
        hexa = strtok(NULL, " \"");
    }*/
    
    //hexa = strtok(teste, "\"");
    //printf("%s\n", hexa);
    //decimal = strtol("0x12f", NULL, 0);
    //printf("Dec = %ld\n", decimal);
    //printf("Hex = %lX\n", decimal);
    
    //sprintf(teste, "%20ld", strtol("0x00000400", NULL, 16));
    //printf("%s\n", teste);
    
    //scanf("%s", hexa);
    //decimal = hexa_para_decimal(teste);
    //printf("%ld\n", decimal);
    //free(hexa);
    
    //scanf("%d", &decimal);
    //printf("%s\n", transforma_dec_para_hexa(decimal));
    
    /*scanf("%d", &decimal);
    transforma_dec_para_hexa(decimal, hexa);
    printf("%s\n", hexa);*/  
    
    return 0;
}
