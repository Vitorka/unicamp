/* Nome: Vitor Kaoru Aoki
 * RA: 178474
 * Laboratorio 06 - Operações em ABB Auto-ajustáveis */

typedef struct n
{
    int item;
    struct n *esq, *dir, *pai;
} no;

/*Funcao que insere um no na arvore*/
no *insere_no(int elemento, no *no_pai);

/*Funcao que realiza a rotacao para a direita*/
no *rotacao_dir(no *no_atual);

/*Funcao que realiza a rotacao para a esquerda*/
no *rotacao_esq(no *no_atual);

/*Funcao que realiza o afunilamento da arvore*/
no *afunilamento(no *no_atual);

/*Funcao que insere um elemento na arvore*/
no *insere(int elemento, no *no_atual);

/*Funcao que busca um elemento na arvore*/
no *busca(int elemento, no *no_atual);

/*Funcao que realiza a busca do no que ira substituir o no que foi retirado*/
no *remove_busca(no *no_atual);

/*Funcao que remove um elemento da arvore*/
no *remove_no(int elemento, no *no_atual);

/*Funcao que cria a arvore a partir da entrada dada*/
no *cria_arvore(no *raiz);

/*Funcao que realiza as operacoes dadas*/
no *realiza_operacoes(no *raiz);

/*Funcao que imprime os nos da arvore em in-ordem*/
void inordem(no *no_atual);

/*Funcao que imprime os nos da arvore em pre-ordem*/
void pre_ordem(no *no_atual);

/*Funcao que desaloca a arvore criada*/
void desaloca(no *no_atual);