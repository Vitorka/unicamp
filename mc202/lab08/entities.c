/* Nome: Vitor Kaoru Aoki 
 * RA: 178474
 * Laboratorio 08 - Detecção de Colisoes */

#include <stdlib.h>

#include "entities.h"

ball* entity_createBall(int id, double x, double y, double vx, double vy, double radius) {
    ball *novo_objeto;
    
    novo_objeto = malloc(sizeof(ball));
    
    novo_objeto->id = id;
    novo_objeto->x = x;
    novo_objeto->y = y;
    novo_objeto->vx = vx;
    novo_objeto->vy = vy;
    novo_objeto->radius = radius;
    
    return novo_objeto;
}

void entity_destroyBall(ball *b) {
    free(b);
}
