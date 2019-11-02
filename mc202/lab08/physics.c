/* Nome: Vitor Kaoru Aoki 
 * RA: 178474
 * Laboratorio 08 - Detecção de Colisoes */

#include "physics.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

void physics_update(qtree *tree, list *entities) {
    node *no_lista;
    
    /*Percorre toda a lista de objetos para atualizar as posicoes dos objetos*/
    for(no_lista = entities->head; no_lista != NULL; 
        no_lista = no_lista->next)
    {
        /*Atualiza as posicoes dos objetos por meio de suas velocidades*/
        no_lista->b->x += no_lista->b->vx;
        no_lista->b->y += no_lista->b->vy;
        
        /*Caso o noh tenha ultrapassado a borda esquerda, faz a sua reflexao*/
        if(no_lista->b->x < 0)
        {
            no_lista->b->x = 0;
            no_lista->b->vx *= -1;
        }
        
        /*Caso o noh tenha ultrapassado a borda superior, faz a sua reflexao*/
        if(no_lista->b->y < 0)
        {
            no_lista->b->y = 0;
            no_lista->b->vy *= -1;
        }
        
        /*Caso o noh tenha ultrapassado a borda direita, faz a sua reflexao*/
        if((no_lista->b->x) + (no_lista->b->radius * 2) >= (tree->root->w))
        {
            no_lista->b->x = tree->root->w - 1 - (2 * no_lista->b->radius);
            no_lista->b->vx *= -1;
        }
        
        /*Caso o noh tenha ultrapassado a borda inferior, faz a sua reflexao*/
        if((no_lista->b->y) + (no_lista->b->radius * 2) >= (tree->root->h))
        {
            no_lista->b->y = tree->root->h - 1 - (2 * no_lista->b->radius);
            no_lista->b->vy *= -1;
        }
    }
}
