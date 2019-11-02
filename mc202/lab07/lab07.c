/* Nome: Vitor Kaoru Aoki 
 * RA: 178474 
 * Laboratorio 07 - Filas de Prioridade com Duas Extremidades */

#include "lab07.h"

/*Funcao que zera o vetor de structs*/
void zera_vetor(Heap heap[MAX])
{
    int i;
    
    for(i = 0; i < MAX; i++)
    {
        heap[i].minimo = 0;
        heap[i].maximo = 0;
    }
}

/*Funcao que verifica se os intervalos de minimo e maximo estao corretos*/
void verifica_maximo_minimo(int posicao, Heap heap[MAX])
{
    int elemento;
    
    /*Caso o minimo do intervalo seja maior que o maximo, inverte os dois*/
    if(heap[posicao].minimo > heap[posicao].maximo)
    {
        elemento = heap[posicao].minimo;
        heap[posicao].minimo = heap[posicao].maximo;
        heap[posicao].maximo = elemento;
    }
}

/*Funcao que organiza o heap de entrada, corrigindo os intervalos*/
void arruma_heap(int num_elem, Heap heap[MAX])
{
    int i, posicao_inicial;
    
    /*Armazena a posicao do ultimo no que nao eh folha*/
    posicao_inicial = (((num_elem - 1) / 2) - 1) / 2;
    
    /*Realiza a organizacao da arvore a partir do ultimo no que nao eh folha*/
    for(i = posicao_inicial; i >= 0; i--)
    {
        desce_heap_minimo(num_elem, i, heap);
        desce_heap_maximo(num_elem, i, heap);  
    }
}

/*Funcao que cria o heap inicial*/
void cria_heap(int num_elem, Heap heap[MAX])
{
    int i;
    
    /*Le os valores do intervalo dado na entrada*/
    for(i = 0; i < ((num_elem + 1) / 2); i++)
    {
        scanf("%d", &heap[i].minimo);
        
        heap[i].maximo = heap[i].minimo;
        
        if(i != (num_elem / 2))
        {
            scanf("%d", &heap[i].maximo);
        }
        
        verifica_maximo_minimo(i, heap);
    }
}

/*Funcao que realiza as operacoes dadas*/
void operacoes(int *num_elem, Heap heap[MAX])
{
    int elemento;
    char operacao;
    
    scanf(" ");
    scanf("%c", &operacao);
    
    /*Le as operacoes ate chegar ao final, representado pelos caracteres 'f' ou 
    'F'*/
    while((operacao != 'f') && (operacao != 'F'))
    {
        switch(operacao)
        {
            /*Caso a operacao dada for 'i', realiza a insercao*/
            case 'i':
                scanf("%d", &elemento);
                insere(num_elem, elemento, heap);
                break;
                
            /*Caso a operacao dada for 'm', realiza a remocao de minimo*/
            case 'm':
                remocao(num_elem, operacao, heap); 
                break;
                    
            /*Caso a operacao dada for 'M', realiza a remocao de maximo*/
            case 'M':
                remocao(num_elem, operacao, heap); 
                break;
        }
        
        scanf(" ");
        scanf("%c", &operacao);
    }
}

/*Funcao que realiza a descida no heap de minimo*/
void desce_heap_minimo(int num_elem, int posicao, Heap heap[MAX])
{
    int elemento, filho_esq, filho_dir, filho_troca;
    
    verifica_maximo_minimo(posicao, heap);
    
    /*Armazena as posicoes do filho esquerdo e direito*/
    filho_esq = (2 * posicao) + 1;
    filho_dir = (2 * posicao) + 2;
    
    /*Caso o filho esquerdo exista, tem como fazer a comparacao para a troca*/
    if(filho_esq <= (num_elem - 1) / 2)
    {
        /*Verficia se o filho direito existe, e caso exista, verifica se o seu 
        minimo eh menor do que o minimo do filho esquerdo*/
        if((filho_dir <= (num_elem - 1) / 2) && 
           (heap[filho_dir].minimo < heap[filho_esq].minimo))
        {
            filho_troca = filho_dir;
        }
        /*Minimo do filho esquerdo eh menor que o minimo do filho direito*/
        else
        {
            filho_troca = filho_esq;
        }
        
        /*Caso o filho de menor minimo, tiver o minimo menor que o do pai, 
        realiza a troca entre eles*/
        if(heap[filho_troca].minimo < heap[posicao].minimo)
        {
            elemento = heap[posicao].minimo;
            heap[posicao].minimo = heap[filho_troca].minimo;
            
            /*Caso o numero de elementos for impar e esteja no ultimo no, apos 
            realizar a troca dos minimos do pai e do filho, iguala o maximo do 
            filho ao seu novo minimo*/
            if(heap[filho_troca].minimo == heap[filho_troca].maximo)
            {
                heap[filho_troca].minimo = elemento;
                heap[filho_troca].maximo = heap[filho_troca].minimo;
            }
            /*Caso contrario, apenas troca o minimo do pai com o do filho*/
            else
            {
                heap[filho_troca].minimo = elemento;
            }
            
            desce_heap_minimo(num_elem, filho_troca, heap);
        }
    }
}

/*Funcao que realiza a descida no heap de maximo*/
void desce_heap_maximo(int num_elem, int posicao, Heap heap[MAX])
{
    int elemento, filho_esq, filho_dir, filho_troca;
    
    verifica_maximo_minimo(posicao, heap);
    
    /*Armazena as posicoes do filho esquerdo e direito*/
    filho_esq = (2 * posicao) + 1;
    filho_dir = (2 * posicao) + 2;
    
    /*Caso o filho esquerdo exista, tem como fazer a comparacao para a troca*/
    if(filho_esq <= (num_elem - 1) / 2)
    {
        /*Verficia se o filho direito existe, e caso exista, verifica se o seu 
        maximo eh maior do que o maximo do filho esquerdo*/
        if((filho_dir <= (num_elem - 1) / 2)  &&
           (heap[filho_dir].maximo > heap[filho_esq].maximo))
        {
            filho_troca = filho_dir;
        }
        /*Maximo do filho esquerdo eh maior que o maximo do filho direito*/
        else
        {
            filho_troca = filho_esq;
        }
        
        /*Caso o filho de maior maximo, tiver o maximo maior que o do pai, 
        realiza a troca entre eles*/
        if(heap[filho_troca].maximo > heap[posicao].maximo)
        {
            elemento = heap[posicao].maximo;
            heap[posicao].maximo = heap[filho_troca].maximo;
            
            /*Caso o numero de elementos for impar e esteja no ultimo no, apos 
            realizar a troca dos maximos do pai e do filho, iguala o minimo 
            do filho ao seu novo maximo*/
            if(heap[filho_troca].minimo == heap[filho_troca].maximo)
            {
                heap[filho_troca].maximo = elemento;
                heap[filho_troca].minimo = heap[filho_troca].maximo;
            }
            /*Caso contrario, apenas troca o maximo do pai com o do filho*/
            else
            {
                heap[filho_troca].maximo = elemento;
            }
      
            desce_heap_maximo(num_elem, filho_troca, heap);
        }   
    }
}

/*Funcao que realiza a subida no heap*/
void sobe_heap(int num_elem, int posicao, Heap heap[MAX])
{
    int posicao_pai;
    
    verifica_maximo_minimo(posicao, heap);
    
    posicao_pai = (posicao - 1) / 2;
    
    /*Verifica se nao chegou a raiz*/
    if(posicao != 0)
    {
        int elemento;
        
        /*Verifica se o elemento a ser trocado eh o de minimo*/
        if(heap[posicao].minimo < heap[posicao_pai].minimo)
        {
            elemento = heap[posicao].minimo;
            
            /*Caso o numero de elementos for impar, e estiver no ultimo no, 
            iguala o maximo do no filho, ao seu novo valor de minimo*/
            if(heap[posicao].minimo == heap[posicao].maximo)
            {
                heap[posicao].maximo = heap[posicao_pai].minimo;
            }
            
            heap[posicao].minimo = heap[posicao_pai].minimo;
            heap[posicao_pai].minimo = elemento;
            sobe_heap(num_elem, posicao_pai, heap);
        }
        /*Verifica se o elemento a ser trocado eh o de maximo*/
        else if(heap[posicao].maximo > heap[posicao_pai].maximo)
        {
            elemento = heap[posicao].maximo;
            
            /*Caso o numero de elementos for impar e o minimo do no filho for 
            maior que o maximo do no pai, troca o minimo do no filho com o 
            maximo do no pai e coloca no filho, o maximo igual ao seu minimo*/
            if(heap[posicao].minimo == heap[posicao].maximo)
            {
                heap[posicao].minimo = heap[posicao_pai].maximo;
                heap[posicao].maximo = heap[posicao].minimo;
            }
            /*Caso o maximo do filho seja maior que o maximo do pai, apenas 
            troca os maximos dos dois*/
            else
            {
                heap[posicao].maximo = heap[posicao_pai].maximo;
            }
            
            heap[posicao_pai].maximo = elemento;
            sobe_heap(num_elem, posicao_pai, heap);
        }
    }
}

/*Funcao que insere um elemento no heap*/
void insere(int *num_elem, int elemento, Heap heap[MAX])
{
    int posicao;
    
    posicao = (*num_elem) / 2;
    
    /*Se o numero de elementos for par, faz o minimo do elemento inserido ser 
    igual ao maximo*/
    if((*num_elem) % 2 == 0)
    {
        heap[posicao].minimo = elemento;
        heap[posicao].maximo = elemento;
    }
    /*Se o numero de elementos for impar, apenas insere o elemento na ultima 
    posicao livre*/
    else
    {
        heap[posicao].maximo = elemento;
    }
    
    sobe_heap((*num_elem), posicao, heap);
    (*num_elem)++;
}

/*Funcao que remove um elemento do heap*/
void remocao(int *num_elem, char operacao, Heap heap[MAX])
{
    int posicao;
    
    posicao = ((*num_elem) - 1) / 2;
    
    /*Caso o heap esteja vazio, indica que a fila esta vazia*/
    if((*num_elem) == 0)
    {
        printf("Fila vazia!\n");
    }
    /*Caso contrario, realiza ou a remocao de minimo ou a remocao de maximo*/
    else
    {
        /*Remocao de minimo*/
        if(operacao == 'm')
        {   
            printf("%d\n", heap[0].minimo);
            heap[0].minimo = heap[posicao].minimo;
            heap[posicao].minimo = heap[posicao].maximo;
            
            desce_heap_minimo((*num_elem), 0, heap);
        }
        /*Remocao de maximo*/
        else 
        {
            printf("%d\n", heap[0].maximo);
            
            /*Verifica se o numero de elementos eh impar*/
            if((*num_elem) % 2 != 0)
            {
                heap[0].maximo = heap[posicao].minimo;
            }
            /*Verifica se o numero de elementos eh par*/
            else
            {
                heap[0].maximo = heap[posicao].maximo;
            }
            
            heap[posicao].maximo = heap[posicao].minimo;
            desce_heap_maximo((*num_elem), 0, heap);
        }
        
        (*num_elem)--;
    }
}

/*Funcao que imprime o heap minimo em pre-ordem*/
void imprime_preordem_min(int num_elem, int posicao, Heap heap[MAX])
{
    /*Imprime caso o heap nao esteja vazio ou nao tenha chegado na ultima 
    posicao*/
    if((posicao <= (num_elem - 1) / 2) && (num_elem != 0))
    {
        printf("%3d ", heap[posicao].minimo);
        imprime_preordem_min(num_elem, (posicao * 2) + 1, heap);
        imprime_preordem_min(num_elem, (posicao * 2) + 2, heap);
    }
}

/*Funcao que imprime o heap maximo em pre-ordem*/
void imprime_preordem_max(int num_elem, int posicao, Heap heap[MAX])
{
    /*Imprime caso o heap nao esteja vazio ou nao tenha chegado na ultima 
    posicao*/
    if((posicao <= (num_elem - 1) / 2) && (num_elem != 0))
    {
        printf("%3d ", heap[posicao].maximo);
        imprime_preordem_max(num_elem, (posicao * 2) + 1, heap);
        imprime_preordem_max(num_elem, (posicao * 2) + 2, heap);
    }
}

/*Funcao que imprime os heaps*/
void imprime(int num_elem, Heap heap[MAX])
{
    printf("\n");
    printf("Min-heap: ");
    imprime_preordem_min(num_elem, 0, heap);
    printf("\n");
    
    printf("Max-heap: ");
    imprime_preordem_max(num_elem, 0, heap);
    printf("\n");
}

