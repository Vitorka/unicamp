/* Nome: Vitor Kaoru Aoki 
 * RA: 178474
 * Laboratorio 08 - Detecção de Colisoes */

#include <stdio.h>
#include <stdlib.h>
#include "entities.h"
#include "list.h"
#include "quadtree.h"
#include "physics.h"

int main(int argc, char *argv[]) {
    int iteracoes, num_objetos;
    int quadtree_total = 0;
        
    scanf("%d", &iteracoes);
    scanf("%d", &num_objetos);
    
    int *objetos_totais = calloc(num_objetos, sizeof(int));
    int max_obj, max_nivel, largura_raiz, altura_raiz;
    
    scanf("%d", &max_obj);
    scanf("%d", &max_nivel);
    scanf("%d", &largura_raiz);
    scanf("%d", &altura_raiz);
    
    int id, i;
    double posicao_x, posicao_y, velocidade_x, velocidade_y, raio;
    ball *novo_objeto;
    list *lista_objetos = list_create();
    
    /*Leitura e armazenamento dos objetos em uma lista*/
    for(i = 0; i < num_objetos; i++)
    {
        scanf("%d", &id);
        scanf("%lf", &posicao_x);
        scanf("%lf", &posicao_y);
        scanf("%lf", &velocidade_x);
        scanf("%lf", &velocidade_y);
        scanf("%lf", &raio);
        
        novo_objeto = entity_createBall(id, posicao_x, posicao_y, velocidade_x, 
                                     velocidade_y, raio);
        list_insertBack(lista_objetos, novo_objeto);
    }
    
    qtree *quadtree;
    
    /*Realiza as iteracoes*/
    for(i = 0; i < iteracoes; i++)
    {   
        /*Cria a quadtree*/
        quadtree = qtree_create(largura_raiz, altura_raiz, max_nivel, 
                                 max_obj);
        
        /*Atualiza os objetos*/
        physics_update(quadtree, lista_objetos);
        
        node *no_lista;
        
        /*Realiza a insercao dos objetos na quadtree*/
        for(no_lista = lista_objetos->head; no_lista != NULL; 
            no_lista = no_lista->next)
        {
            qtree_insert(quadtree, quadtree->root, no_lista->b);
        }
        
        int j;
        
        /*Contabiliza a quantidade de colisoes possiveis para cada objeto*/
        for(no_lista = lista_objetos->head, j = 0; no_lista != NULL; 
            no_lista = no_lista->next, j++)
        {
            list *objects = list_create();
            
            double x = no_lista->b->x;
            double y = no_lista->b->y;
            double w = no_lista->b->radius * 2;
            double h = no_lista->b->radius * 2;
            
            qtree_retrieve(quadtree->root, x, y, w, h, objects);
            list_remove(objects, no_lista->b);
            objetos_totais[j] += objects->size;
            list_free(objects);
        }
        
        /*Destroi a quadtree*/
        qtree_destroy(quadtree);
    }
    
    /*Contabiliza as colisoes totais pelo metodo forca bruta*/
    int forca_bruta = num_objetos * (num_objetos - 1) * iteracoes;
    int j;
    
    /*Contabiliza as colisoes totais pelo metodo Quadtree*/
    for(j = 0; j < num_objetos; j++)
    {
        quadtree_total += objetos_totais[j];
    }
    
    printf("Forca-Bruta: %d\n", forca_bruta);
    printf("QuadTree: %d\n", quadtree_total);
    for(j = 0; j < num_objetos; j++)
    {
        printf("Objeto %d: %d\n", j, objetos_totais[j]);
    }
    
    /*Desaloca todas as listas e apontadores para objetos criados*/
    free(objetos_totais);
    
    node *no_lista;
    for(no_lista = lista_objetos->head; no_lista != NULL; 
        no_lista = no_lista->next)
    {
        entity_destroyBall(no_lista->b);
    }
    list_free(lista_objetos);
    
    return 0;
}
