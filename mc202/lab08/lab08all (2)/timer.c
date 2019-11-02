#include <string.h>

#include "timer.h"

void timer_initialize(timer *t) {
    memset((void*) t, 0, sizeof(timer));
}

void timer_start(timer *t) {
    t->started = true;
    t->paused = false;
    t->startTicks = SDL_GetTicks();
    t->pausedTicks = 0;
}

void timer_stop(timer *t) {
    memset((void*) t, 0, sizeof(timer));
}

void timer_pause(timer *t) {
    if (t->started && !t->paused) {
        t->paused = true;
        t->pausedTicks = SDL_GetTicks() - t->startTicks;
        t->startTicks = 0;
    }
}

void timer_unpause(timer *t) {
    if (t->started && t->paused) {
        t->paused = false;
        t->startTicks = SDL_GetTicks() - t->pausedTicks;
        t->pausedTicks = 0;
    }
}

Uint32 timer_getTicks(timer *t) {
    Uint32 time = 0;

    if (t->started) {
        if (t->paused) {
            time = t->pausedTicks;
        } else {
            time = SDL_GetTicks() - t->startTicks;
        }
    }

    return time;
}

bool timer_isStarted(timer *t) {
    return t->started;
}

bool timer_isPaused(timer *t) {
    return t->paused;
}
