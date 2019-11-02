#include "core.h"
#include "quadtree.h"
#include "physics.h"
#include "timer.h"

int main(int argc, char *argv[]) {
    int nIterations, nObjects;
    int maxObjects, maxLevels, width, height;
    list *entities = list_create(); // aqui vão os objetos lidos do stdin
   
    // inicialize as variáveis acima antes de chamar as próximas funções

    core_initialize(width, height, maxLevels, maxObjects);
    core_insertObjects(entities);
    core_setMaxIterations(nIterations);
    core_run();
    core_shutdown();

    return 0;
}
