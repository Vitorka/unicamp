#include <time.h>
#include <stdlib.h>

#include <SDL2/SDL_image.h>

#include "core.h"
#include "list.h"
#include "timer.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define SCREEN_FPS 60.0
#define SCREEN_TICK_PER_FRAME 1000 / SCREEN_FPS

#define MAX_ABS_SPEED 100
#define MIN_ABS_SPEED 100

struct _core {
    // Uso interno do SDL.
    SDL_Window *window;
    SDL_Renderer *renderer;

    // Informações da quadtree. 
    int width;
    int height;
    int maxDepth;
    int maxObjectsPerNode;

    qtree* tree;
    list* entities;

    int maxIterations;
};
typedef struct _core Core;

// Acesso global a diversas informações do SDL / QuadTree. 
// Evita passagem de parâmetros excessiva.
static Core gCore;

static bool objectsIntersect(ball *collider, ball *collidee) {
    double centerColliderX = collider->x + collider->radius;
    double centerColliderY = collider->y + collider->radius;
    double centerCollideeX = collidee->x + collidee->radius;
    double centerCollideeY = collidee->y + collidee->radius;

    return sqrt(pow(centerColliderX - centerCollideeX, 2) 
            + pow(centerColliderY - centerCollideeY, 2)) <= collider->radius +
        collidee->radius;
}

static void render_tree(qnode *root) {
    if (root == NULL) {
        return;
    }

    SDL_SetRenderDrawColor(gCore.renderer, 0x0, 0xff, 0x0, 0xff);
    SDL_Rect rect = { .x = root->x, .y = root->y, .w = root->w, .h = root->h };
    SDL_RenderDrawRect(gCore.renderer, &rect); 
    for (int i = 0; i < 4; i++) {
        render_tree(root->children[i]);
    }
}

bool core_initialize(int width, int height, int maxDepth, int maxObjectsPerNode) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("[Error] Could not initialize SDL: %s\n", SDL_GetError());
        return false;
    }

    gCore.window = SDL_CreateWindow("MC202 - Particle Collider", 
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (gCore.window == NULL) {
        printf("[Error] Could not create window: %s\n", SDL_GetError());
        return false;
    }

    gCore.renderer = SDL_CreateRenderer(gCore.window, -1, SDL_RENDERER_SOFTWARE);
    if (gCore.renderer == NULL) {
        printf("[Error] Could not create a renderer for window: %s\n", SDL_GetError());
        return false;
    }

    if (!IMG_Init(IMG_INIT_PNG)) {
        printf("[Error] Could not initialize SDL Image: %s\n", IMG_GetError());
    }

    gCore.entities = list_create();
    gCore.width = width;
    gCore.height = height;
    gCore.maxDepth = maxDepth;
    gCore.maxObjectsPerNode = maxObjectsPerNode;
    gCore.maxIterations = -1;

    return true;
}

void core_insertObjects(list *initialObjects) {
    list_concatenate(gCore.entities, initialObjects);
}

void core_setMaxIterations(int maxIterations) {
    gCore.maxIterations = maxIterations;
}

void core_run() {
    srand(time(NULL));

    bool quit = false;

    SDL_Event e;
    timer fpsTimer;
    timer capTimer;

    int countedFrames = 0;
    timer_start(&fpsTimer);

    // Um pequeno hack para carregar uma textura otimizada do SDL
    // escondendo toda a implementação do header de entidade.
    SDL_Surface *ballTexture = IMG_Load("circle.png");
    if (SDL_GetWindowSurface(gCore.window) == NULL) {
        printf("[Error] Window Surface is NULL: %s\n", SDL_GetError());
        exit(0);
    }
    SDL_Surface *optimizedTexture = SDL_ConvertSurface(ballTexture, 
            SDL_GetWindowSurface(gCore.window)->format, 0);
    SDL_FreeSurface(ballTexture);

    // Popula a lista inicial de objetos com a textura. 
    node *cur = gCore.entities->head;
    while (cur != NULL) {
        cur->b->texture = optimizedTexture;
        cur = cur->next;
    }

    int nIterations = 0;
    while (!quit) {
        int startTicks = timer_getTicks(&capTimer);

        timer_start(&capTimer);
        gCore.tree = qtree_create(gCore.width, gCore.height, gCore.maxDepth,
                gCore.maxObjectsPerNode);

        node *prevEntities = gCore.entities->head;
        while (prevEntities != NULL) {
            qtree_insert(gCore.tree, gCore.tree->root, prevEntities->b);
            prevEntities = prevEntities->next;
        }

        while (SDL_PollEvent(&e) != 0) {
            switch (e.type) {
                case SDL_QUIT:
                    quit = true;
                    break;

                case SDL_MOUSEBUTTONDOWN: {
                    printf("[Warn] Spawning ball.\n");
                    int mX, mY;
                    SDL_GetMouseState(&mX, &mY);
                    ball *b = entity_createBall(0, mX - optimizedTexture->w / 2, 
                            mY - optimizedTexture->h / 2, 
                            (2 * (rand() % MAX_ABS_SPEED) - MAX_ABS_SPEED) / SCREEN_FPS, 
                            (2 * (rand() % MAX_ABS_SPEED) - MAX_ABS_SPEED) / SCREEN_FPS,
                            optimizedTexture->w / 2);
                    b->texture = optimizedTexture;

                    list_insertBack(gCore.entities, b);
                    qtree_insert(gCore.tree, gCore.tree->root, b);
                    break;
                }
            }
        }

        float avgFPS = countedFrames / ( timer_getTicks(&fpsTimer) / 1000.f );
        if(avgFPS > 2000000 ) {
            avgFPS = 0;
        }

        if (gCore.maxIterations == -1 || nIterations < gCore.maxIterations) {
            core_update(startTicks);
        }
        nIterations++;

        SDL_SetRenderDrawColor(gCore.renderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gCore.renderer);

        core_render();

        SDL_RenderPresent(gCore.renderer);
        ++countedFrames;

        int frameTicks = timer_getTicks(&capTimer);
        if (frameTicks < SCREEN_TICK_PER_FRAME) {
            SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicks);
        }

        qtree_destroy(gCore.tree);
    }

    SDL_FreeSurface(optimizedTexture);
}

void core_update(int timeStep) {
    physics_update(gCore.tree, gCore.entities);
}

void core_render() {
    SDL_Surface *windowSurface = SDL_GetWindowSurface(gCore.window);
    SDL_Rect stretchRect;

    render_tree(gCore.tree->root); 

    node *cur = gCore.entities->head;
    while (cur != NULL) {
        stretchRect.x = cur->b->x;
        stretchRect.y = cur->b->y;
        stretchRect.w = 2 * cur->b->radius;
        stretchRect.h = 2 * cur->b->radius;

        SDL_BlitScaled(cur->b->texture, NULL, windowSurface, &stretchRect);

        cur = cur->next;        
    }
}

void core_shutdown() {
    if (gCore.renderer != NULL) {
        SDL_DestroyRenderer(gCore.renderer);
    }
    if (gCore.window != NULL) {
        SDL_DestroyWindow(gCore.window);
    }
    IMG_Quit();

    gCore.renderer = NULL;
    gCore.window = NULL;

    node *cur = gCore.entities->head;
    while (cur != NULL) {
        entity_destroyBall(cur->b);
        cur = cur->next;
    }
    list_free(gCore.entities);
}
