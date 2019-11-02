#ifndef CORE_H_INCLUDED_
#define CORE_H_INCLUDED_ 

#include <SDL2/SDL.h>

#include <stdbool.h>

#include "physics.h"

/*
 * @nome: core_initialize
 * @descr: Inicializa a biblioteca de visualização.
 * @param:
 *  @width: largura da raiz da quadtree
 *  @height: altura da raiz da quadtree
 *  @maxDepth: profundidade máxima da quadtree
 *  @maxObjectsPerNode: número máximo de objetos por nó
 * @retorna: True, se todos os módulos forem inicializados com sucesso. Falso, caso contrário.
 *
 * Obs: Essa função deve ser chamada antes de qualquer outra função do módulo core.
 */
bool core_initialize(int width, int height, int maxDepth, int maxObjectsPerNode);

/*
 * @nome: core_insertObjects
 * @descr: Insere uma lista de objetos. Essa rotina é útil caso você deseje
 * ler um arquivo de entrada do laboratório e usar como estado inicial do visualizador.
 *
 * @param:
 *  @initialObjects: lista contendo os objetos a serem adicionados.
 * @retorna: Nada.
 */
void core_insertObjects(list *initialObjects);

/*
 * @nome: core_setMaxIterations
 * @descr: Coloca um limite máximo para o número de iterações. Quando esse limite é
 * atingido, os objetos param de ser atualizados.
 *
 * @param:
 *  @maxIterations: número máximo de iterações ou -1, para não colocar limite.
 * @retorna: Nada.
 */
void core_setMaxIterations(int maxIterations);

/*
 * @nome: core_run
 * @descr: Executa o visualizador.
 *
 * @param: Nenhum.
 * @retorna: Nada.
 */
void core_run();

/*
 * @nome: core_update
 * @descr: Atualiza todos os objetos da quadtree.
 *
 * @param:
 *  @timeStep: Quantidade de tempo (em milisegundos) decorrida desde o último frame.
 * @retorna: Nada.
 */
void core_update(int timeStep);

/*
 * @nome: core_render
 * @descr: Desenha a quadtree e todos os objetos nela contidos.
 *
 * @param: Nenhum.
 * @retorna: Nada.
 */
void core_render();

/*
 * @nome: core_shutdown
 * @descr: Desliga todas as bibliotecas auxiliares e desaloca toda a memória utilizada.
 *
 * @param: Nenhum.
 * @retorna: Nada.
 */
void core_shutdown();

#endif /* CORE_H_INCLUDED_ */
