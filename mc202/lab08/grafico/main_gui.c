#include "core.h"
#include "quadtree.h"
#include "physics.h"
#include "timer.h"

int main(int argc, char *argv[]) {
    int nIterations, nObjects;
    int maxObjects, maxLevels, width, height;
    list *entities = list_create(); // aqui vão os objetos lidos do stdin
   
    scanf("%d", &nIterations);
    scanf("%d", &nObjects);
    
    scanf("%d", &maxObjects);
    scanf("%d", &maxLevels);
    scanf("%d", &width);
    scanf("%d", &height);
    
    int id, i;
    double posicao_x, posicao_y, velocidade_x, velocidade_y, raio;
    ball *novo_objeto;
    list *lista_objetos = list_create();
    
    /*Leitura e armazenamento dos objetos em uma lista*/
    for(i = 0; i < nObjects; i++)
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
    
    // inicialize as variáveis acima antes de chamar as próximas funções

    core_initialize(width, height, maxLevels, maxObjects);
    core_insertObjects(entities);
    core_setMaxIterations(nIterations);
    core_run();
    core_shutdown();

    return 0;
}
