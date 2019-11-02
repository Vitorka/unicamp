#ifndef ENTITIES_H_INCLUDED_
#define ENTITIES_H_INCLUDED_ 

#ifdef RENDER_SIMULATION_FLAG
#include <SDL2/SDL.h>
#endif

struct _ball {
    int id; // ID único de cada objeto

    double x; // Posição x do objeto na tela
    double y; // Posição y do objeto na tela
    double vx; // Velocidade, em pixels / frame, na direção x
    double vy; // Velocidade, em pixels / frame, na direção y
    double radius; // Raio, em pixels.

    #ifdef RENDER_SIMULATION_FLAG
    SDL_Surface *texture; // Referência para a textura. Não mexa :)
    #endif
};
typedef struct _ball ball;

/*
 * @nome: entity_createBall
 * @descr: Cria um objeto do tipo ball.
 * 
 * @param:
 *  @id: Id único (não negativo, não zero).
 *  @x: Posição x do objeto.
 *  @y: Posição y do objeto.
 *  @vx: Velocidade, em pixels / frame, na direção x
 *  @vy: Velocidade, em pixels / frame, na direção y
 *  @radius: Raio, em pixels.
 *
 * @retorna: Um ponteiro para o objeto criado.
 */
ball* entity_createBall(int id, double x, double y, double vx, double vy, double radius);

/*
 * @nome: entity_destroyBall
 * @descr: Destrói um objeto do tipo ball.
 * 
 * @param: Nenhum
 * @retorna: Nada.
 *
 *
 * Obs: Essa rotina *não* deve mexer no campo texture.
 */
void entity_destroyBall(ball *b);

#endif /* ENTITIES_H_INCLUDED_ */
