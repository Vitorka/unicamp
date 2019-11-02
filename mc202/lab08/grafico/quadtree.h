#ifndef QUADTREE_H_INCLUDED_
#define QUADTREE_H_INCLUDED_ 

#include "entities.h"
#include "list.h"

struct _qnode {
   struct _qnode *(children[4]); // Vetor de ponteiros para os filhos
   list *objects; // Lista de objetos contidos no nó
   int x, y, w, h; // Retângulo delimitador da região do nó
   int maxObjects; // Número máximo de objetos que o nó pode comportar
   int level; // Nível do nó
};
typedef struct _qnode qnode;

struct _qtree {
    qnode *root;
    int maxDepth;
    int maxObjectsPerNode;
};
typedef struct _qtree qtree;

/*
 * @nome: qtree_create
 * @descr: Cria uma quadtree.
 *
 * @param:
 *  @width: Largura da raiz.
 *  @height: Altura da raiz.
 *  @maxDepth: Profundidade (altura) máxima da árvore.
 *  @maxObjectsPerNode: Número máximo de objetos em um nó.
 *
 * @retorno: Ponteiro para o objeto quadtree.
 */
qtree* qtree_create(int width, int height, int maxDepth, int maxObjectsPerNode);

/*
 * @nome: qtree_destroy
 * @descr: Destrói um objeto quadtree.
 *
 * @param:
 *  @t: Ponteiro para um objeto quadtree.
 *
 * @retorno: Nada.
 */
void qtree_destroy(qtree *t);

/*
 * @nome: qtree_destroyNodes
 * @descr: Destrói a estrutura interna da árvore, mantendo
 * o objeto quadtree intacto.
 *
 * @param:
 *  @root: Ponteiro para um objeto quadtree.
 *
 * @retorno: Nada.
 */
void qtree_destroyNodes(qnode *root);

/*
 * @nome: qtree_getIndex
 * @descr: Descobre o índice do filho que melhor comporta 
 * a região delimitada por (x, y, w, h).
 *
 * @param:
 *  @n: Ponteiro para um nó.
 *  @x: Posição x da região.
 *  @y: Posição y da região.
 *  @w: Largura da região.
 *  @h: Altura da região.
 *
 * @retorno: O índice do filho ou -1, se a região não puder ser inteiramente comportada
 * pelos filhos do nó.
 */
int qtree_getIndex(qnode *n, double x, double y, double w, double h);

/*
 * @nome: qtree_insert
 * @descr: Insere um elemento na árvore.
 *
 * @param:
 *  @tree: Ponteiro para o objeto árvore.
 *  @treeNode: Ponteiro para um nó.
 *  @b: Objeto a ser inserido.
 *
 * @retorno: Nada.
 */
void qtree_insert(qtree *tree, qnode *treeNode, ball *b);

/*
 * @nome: qtree_split
 * @descr: Subdivide um nó em 4 partes.
 *
 * @param:
 *  @n: Ponteiro para o nó a ser dividido.
 *
 * @retorno: nada.
 */
void qtree_split(qnode *n);

/*
 * @nome: qtree_createNode
 * @descr:  Cria um nó delimitado por uma região.
 *
 * @param:
 *  @x: Posição x do nó.
 *  @y: Posição y do nó.
 *  @w: Largura do nó.
 *  @h: Altura do nó.
 *  @maxObjects: Número máximo de objetos que o nó pode comportar.
 *  @level: Nível atual do nó.
 *
 * @retorno: Ponteiro para o nó criado.
 */
qnode* qtree_createNode(int x, int y, int w, int h, int maxObjects, int level);

/*
 * @nome: qtree_retrieve
 * @descr: Retorna todos os objetos contidos na região delimitada
 * por (x, y, w, h) e os armazena em uma lista.
 *
 * @param:
 *  @root: Ponteiro para a raiz da quadtree.
 *  @x: Posição x da região.
 *  @y: Posição y da região.
 *  @w: Largura da região.
 *  @h: Altura da região.
 *  @objects: Lista que irá armazenar os objetos.
 *
 * @retorno: Nada.
 *
 * Obs: A lista deve ter sido alocada previamente.
 */
void qtree_retrieve(qnode *root, double x, double y, double w, double h, list *objects);

#endif /* QUADTREE_H_INCLUDED_ */
