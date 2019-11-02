/* Nome: Vitor Kaoru Aoki
 * RA: 178474
 * Laboratorio 02 - Matrioshkas Generalizadas */

struct p
{
    int item;
    int capacidade;
    struct p *prox;
};
typedef struct p pilha;

/*Funcao que cria uma pilha adicionando o no cabeca*/
pilha *inicia_pilha(pilha *topo);

/*Funcao que adiciona os dados na pilha*/
pilha *cria_pilha(pilha *topo, int dado);

/*Funcao que adiciona o primeiro elemento a pilha*/
pilha *primeiro_elemento(pilha *topo, int dado);

/*Funcao que retira o elemento da pilha caso seja verificado que ele possui uma 
metade correspondente*//*Funcao que desaloca as pilhas criadas*/
pilha *retira(pilha *topo);

/*Funcao que desaloca as pilhas criadas*/
void desaloca(pilha *topo);