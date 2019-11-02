#ifndef PHYSICS_H_INCLUDED_
#define PHYSICS_H_INCLUDED_ 

#include "list.h"
#include "quadtree.h"

#include <stdbool.h>

/*
 * @nome: physics_update
 * @descr: Atualiza a posição de todos os objetos da quadtree. 
 * Esta função também deve refletir um objeto, caso ele passe pelos
 * limites da quadtree.
 *
 * @param:
 *  @tree: Ponteiro para o objeto quadtree.
 *  @entities: Lista de objetos contidos na quadtree.
 *
 * @retorno: Nada
 */
void physics_update(qtree *tree, list *entities);

#endif /* PHYSICS_H_INCLUDED_ */
