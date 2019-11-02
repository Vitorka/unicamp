/* Nome: Vitor Kaoru Aoki 
 * RA: 178474
 * Laboratorio 07 - Filas de Prioridade com Duas Extremidades */

#include "lab07.h"

int main()
{
    int num_elem;
    Heap heap[MAX];
    
    scanf("%d", &num_elem);
    
    cria_heap(num_elem, heap);
    arruma_heap(num_elem, heap);
    operacoes(&num_elem, heap);
    imprime(num_elem, heap);
    
    return 0;
}
    