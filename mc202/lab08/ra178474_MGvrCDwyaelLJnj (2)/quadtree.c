/* Nome: Vitor Kaoru Aoki 
 * RA: 178474
 * Laboratorio 08 - Detecção de Colisoes */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "quadtree.h"

qtree* qtree_create(int width, int height, int maxDepth, 
        int maxObjectsPerNode) {
    
    qtree *quadtree;
    
    quadtree = malloc(sizeof(qtree));
    
    quadtree->root = qtree_createNode(0, 0, width, height, 
                                       maxObjectsPerNode, 0);
    
    quadtree->maxDepth = maxDepth;
    quadtree->maxObjectsPerNode = maxObjectsPerNode;
    
    return quadtree;
}

void qtree_destroy(qtree *t) {
    
    qtree_destroyNodes(t->root);
    free(t);
}

void qtree_destroyNodes(qnode *root) {
    
    if(root->children[0] == NULL)
    {
        list_free(root->objects);
        free(root);
    }
    else
    {
        int i;
        
        for(i = 0; i < 4; i++)
        {
            qtree_destroyNodes(root->children[i]);
        }
        
        list_free(root->objects);
        free(root);
    }   
}

int qtree_getIndex(qnode *n, double x, double y, double w, double h) {
    
    int i;
    
    /*Verifica se o noh atual possui filhos*/
    if(n->children[0] != NULL)
    {
        /*Percorre os filhos e verifica se a regiao do objeto se enquadra em 
        algum deles*/
        for(i = 0; i < 4; i++)
        {
            if((x >= n->children[i]->x) && 
               (y >= n->children[i]->y))
            {
                if(((x + w) < (n->children[i]->x + n->children[i]->w)) && 
                   ((y + h) < (n->children[i]->y + n->children[i]->h)))
                {
                    return i;
                }
            }
        }
    }
    
    return -1;
}

void qtree_split(qnode *n) {
    
    int x, y, w, h, maxObjects, level;
    
    /*Variaveis auxiliares para armazenar as informacoes do noh*/
    x = n->x;
    y = n->y;
    w = n->w; 
    h = n->h; 
    maxObjects = n->maxObjects;
    level = n->level + 1;
    
    /*Cria os nos filhos do noh atual*/
    n->children[0] = qtree_createNode(x, y, w / 2, h / 2, maxObjects, level);
    n->children[1] = qtree_createNode(x + (w / 2), y, w / 2, h / 2, maxObjects, 
                                      level);
    n->children[2] = qtree_createNode(x, y + (h / 2), w / 2, h / 2, maxObjects, 
                                      level);
    n->children[3] = qtree_createNode(x + (w / 2), y + (h / 2), w / 2, h / 2, 
                                      maxObjects, level);
}

qnode* qtree_createNode(int x, int y, int w, int h, int maxObjects, int level) {
    qnode *novo_no;
    
    novo_no = malloc(sizeof(qnode));
    
    novo_no->x = x;
    novo_no->y = y;
    novo_no->w = w;
    novo_no->h = h;
    novo_no->maxObjects = maxObjects;
    novo_no->level = level;
    
    int i;
    
    /*Inicializa o vetor de filhos do noh criado*/
    for(i = 0; i < 4; i++)
    {
        novo_no->children[i] = NULL;
    }
    
    /*Inicializa a lista de objetos do noh criado*/
    novo_no->objects = list_create();
    
    return novo_no;
}

void qtree_insert(qtree *tree, qnode *treeNode, ball *b) {
    
    int return_index;
    
    /*Variaveis auxiliares para armazenar as informacoes do objeto*/
    double x = b->x;
    double y = b->y;
    double w = b->radius * 2;
    double h = b->radius * 2;
    
    return_index = qtree_getIndex(treeNode, x, y, w, h);
    
    /*Caso exista filho e seja possivel inserir nele, realiza a insercao*/
    if(return_index != -1)
    {
        qtree_insert(tree, treeNode->children[return_index], b);
    }
    /*Caso nao exista filho ou nao seja possivel inserir o objeto em um dos 
    filhos, insere o objeto no noh atual*/
    else
    {
        /*Insere o objeto no noh atual e depois verifica se deve ser realizado 
        o split e consequente reinsercao dos objetos do noh atual, na arvore*/
        list_insertBack(treeNode->objects, b);
        
        /*Verifica se eh possivel realizar o split*/
        if((treeNode->children[0] == NULL) && 
           (treeNode->level < tree->maxDepth - 1) && 
           (treeNode->objects->size > tree->maxObjectsPerNode))
        {
            /*Realiza o split do noh*/
            qtree_split(treeNode);
            
            node *no_lista;
            
            /*Cria uma lista para armazenar os objetos que serao reinseridos na 
            arvore*/
            list *lista_objetos = list_create();
            list_concatenate(lista_objetos, treeNode->objects);
            list_free(treeNode->objects);
            treeNode->objects = list_create();
            
            /*Percorre a lista de objetos do noh atual para reinseri-los na 
            quadtree*/
            for(no_lista = lista_objetos->head; no_lista != NULL; 
                no_lista = no_lista->next)
            {
                /*Variaveis auxiliares que armazenam as informacoes dos 
                objetos*/
                x = no_lista->b->x;
                y = no_lista->b->y;
                w = no_lista->b->radius * 2;
                h = no_lista->b->radius * 2;
                
                return_index = qtree_getIndex(treeNode, x, y, w, h);
                
                /*Caso seja possivel inserir em algum filho chama a insercao 
                para esse filhol*/
                if(return_index != -1)
                {
                    qtree_insert(tree, treeNode->children[return_index], 
                                 no_lista->b);
                }
                /*Caso contrario reinsere o objeto no noh atual*/
                else
                {
                    list_insertBack(treeNode->objects, no_lista->b);
                }
            }
            
            list_free(lista_objetos);
        }
    }
}

void qtree_retrieve(qnode *root, double x, double y, double w, double h, 
                    list *objects) {
    
    int return_index = qtree_getIndex(root, x, y, w, h);
    
    /*Caso o objeto caiba em algum dos filhos*/
    if(return_index != -1)
    {
        qtree_retrieve(root->children[return_index], x, y, w, h, objects);
    }
    
    list_concatenate(objects, root->objects);
}
