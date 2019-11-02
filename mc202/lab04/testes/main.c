/* Nome: Vitor Kaoru Aoki 
 * RA: 178474 
 * Laboratorio 04 - Soltando bolas em uma árvore */

#include <stdio.h>
#include <stdlib.h>
#include "lab04.h"

int main()
{
    int i, j, num_testes, profundidade, num_bolas, final;
    arv_bin *arv_inicio = NULL;
    
    scanf("%d", &num_testes);
    
    /*Executa todos os casos de testes dados*/
    for(i = 0; i < num_testes; i++)
    {
        scanf("%d %d", &profundidade, &num_bolas);
        
        /*Cria o no apontador para o inicio da arvore*/
        arv_inicio = inicia_arvore(profundidade);
        
        /*Insere o primeiro no da arvore*/
        arv_inicio->raiz = insere_no(1);
        
        /*Cria o restante da arvore*/
        cria_arvore(arv_inicio->raiz, 1, profundidade); 
        
        /*Executa o percurso percorrido pelas bolas*/
        for(j = 0; j < num_bolas; j++)
        {
            final = percurso_bola(arv_inicio->raiz);
        }
        
        printf("%d\n", final);
        desaloca(arv_inicio->raiz);
        free(arv_inicio);
    }
    
    
    return 0;
}

