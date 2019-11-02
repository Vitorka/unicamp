typedef struct n
{
    int item;
    struct n *esq, *dir;
} no;

/*Funcao que le e armazena os percursos in-ordem e pre-ordem*/
void le_percurso(char *percurso, int num_nos);

/*Funcao que insere um no a arvore*/
no *insere_no(char caractere);

/*Funcao que monta a arvore, a partir dos percursos in-ordem e pre-ordem*/
no *monta_arvore(char *pre_ordem, char *in_ordem, int tamanho, int inicio, 
                 int raiz_atual, int num_nos);

/*Funcao que imprime a arvore em pos-ordem*/
void imprime_pos_ordem(no *raiz);

/*Funcao que desaloca a arvore criada*/
void desaloca(no *no_atual);