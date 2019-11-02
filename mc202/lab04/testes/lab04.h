/* Nome: Vitor Kaoru Aoki 
 * RA: 178474 
 * Laboratorio 04 - Soltando bolas em uma árvore */

struct n
{
    int item;
    unsigned int flag;
    struct n *esq, *dir;
};
typedef struct n no;

struct binary_tree {
    no* raiz;
    int prof;
};
typedef struct binary_tree arv_bin;

/*Funcao que cria a arvore com sua respectiva raiz*/
arv_bin *inicia_arvore(int profundidade);

/*Funcao que insere um novo no, com seu respectivo valor, na arvore*/
no *insere_no(int posicao);

/*Funcao que cria a arvore*/
void cria_arvore(no *no_atual, int posicao, int profundidade);

/*Funca que percorre a arvore, realizando o percurso seguido pela bola*/
int percurso_bola(no *no_atual);

/*Funcao que desaloca a arvore criada*/
void desaloca(no *no_atual);
