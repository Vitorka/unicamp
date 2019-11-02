/*Nome: Vitor Kaoru Aoki
  RA: 178474
*/

#include <stdio.h>

/*O programa testara os valores possiveis obtidos atraves da compra e venda de 
acoes. Esses valores sao calculados de acordo com o valor do capital inicial 
de Jordan Belfort e com os valores das acoes em um numero D de dias. Ao final, 
ele indica se e lucrativo ou nao realizar a compra e venda das acoes*/
int main(){
    
    int i, j, k, l, dias, cap_ini, val_acao[100], acoes1 = 0, acoes2 = 0, 
    venda1 = 0, venda2 = 0, valor_fin;
    
    scanf("%d %d", &dias, &cap_ini);
    
    for(i = 0; i < dias; i++) { 
        val_acao[i] = 0;
    }
    
    for(i = 0; i < dias; i++) {
        scanf("%d", &val_acao[i]);
    }
    
    /*Calcula os valores iniciais de acoes que e possivel obter a partir do 
    capital inicial*/
    for(i = 0, valor_fin = cap_ini; i < dias; i++) {    
        acoes1 = cap_ini / val_acao[i];
        
        /*A partir desse numero de acoes obtidas, calcula os primeiros valores 
        de venda possiveis*/
        for(j = i + 1; j < dias; j++) {    
            venda1 = (acoes1 * val_acao[j]) + (cap_ini % val_acao[i]);     
            
            /*Com esse valor obtido da primeira venda, calcula as novas 
            quantidades de acoes que sao possiveis comprar*/
            for(k = j + 1; k < dias; k++) {
                acoes2 = venda1 / val_acao[k];
                
                /*A partir do numero de acoes obtidas com a segunda compra, 
                realiza as ultimas vendas possiveis*/
                for(l = k + 1; l < dias; l++) {
                    venda2 = (acoes2 * val_acao[l]) + (venda1 % val_acao[k]);
                    
                    /*Verifica se houve lucro, apos as compras e vendas das 
                    acoes, e no caso de haver lucro, qual foi o maior*/
                    if(venda2 > valor_fin) {
                        valor_fin = venda2;
                    }
                }
            }
        
            /*Condicao para intervalos de dias onde apenas uma compra e 
            uma venda sao lucrativos*/
            if(venda1 > valor_fin) {   
                valor_fin = venda1;
            }
        }
    }
    
    if(valor_fin == cap_ini) {    
        printf("Melhor nao investir agora, cara!\n");
    } else {
        printf("Capital final = R$%d\n", valor_fin);
    }
    return 0;
}