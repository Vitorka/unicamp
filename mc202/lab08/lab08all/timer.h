#ifndef TIMER_H_INCLUDED_
#define TIMER_H_INCLUDED_ 

#include <SDL2/SDL.h>

#include <stdbool.h>

struct _timer {
    // Tempo do clock quando o timer começou.
    Uint32 startTicks;
    // Tempo quando o timer foi pausado.
    Uint32 pausedTicks;

    bool paused;
    bool started;
};
typedef struct _timer timer;

/*
 * @nome: timer_initialize
 * @descr: Inicializa um objeto timer
 *
 * @param: Um ponteiro para um timer.
 * @retorna: Nada.
 */
void timer_initialize(timer *t);

/*
 * @nome: timer_start
 * @descr: Liga o timer.
 *
 * @params: Pointe para um objeto timer.
 * @retorna: Nada.
 */
void timer_start(timer *t);

/*
 * @nome: timer_stop
 * @descr: Para o timer.
 *
 * @param: Um ponteiro para um timer.
 * @retorna: Nada.
 */
void timer_stop(timer *t);

/*
 * @nome: timer_pause
 * @descr: Pausa o timer.
 *
 * @param: Um ponteiro para um timer.
 * @retorna: Nada.
 */
void timer_pause(timer *t);

/*
 * @nome: timer_unpause
 * @descr: Despausa o timer.
 *
 * @param: Ponteiro para um objeto timer.
 * @retorna: Nada.
 */
void timer_unpause(timer *t);

/*
 * @nome: timer_getTicks
 * @descr: Retorna o tempo decorrido desde que o timer foi
 * ligado, em milisegundos.
 *
 * @param: Ponteiro para um timer.
 * @retorna: Tempo decorrido, em milisegundos.
 */
Uint32 timer_getTicks(timer *t);

/*
 * @nome: timer_isStarted
 * @descr: Verifica se o timer está ligado.
 *
 * @param: Ponteiro para um timer.
 * @retorna: Verdadeiro, se o timer estiver ligado. Falso, caso contrário.
 */
bool timer_isStarted(timer *t);

/*
 * @nome: timer_isPaused
 * @descr: Verifica se o timer está pausado.
 *
 * @param: Ponteiro para um timer.
 * @retorna: Verdadeiro, se o timer foi pausado. Falso, caso contrário.
 */
bool timer_isPaused(timer *t);

#endif /* TIMER_H_INCLUDED_ */
