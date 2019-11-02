/*Nome: Vitor Kaoru Aoki
  RA: 178474
*/

#include <stdio.h>
#include <string.h>
#include <math.h>

/* Definindo tamanho maximo das imagens */
#define MAX_TAM 400

/* Le uma imagem em formato PGM a partir da entrada padrao.
 * Retorna 1 se a leitura for realmente de um arquivo PGM
 * e 0 caso contrario */
int ler_pgm(int img[][MAX_TAM], int *W, int *H, int *MaxV,
            int *F, double *C, double *Gama) {
    char nome_formato[3];
    int i,j;
    
    /* Le o formato da imagem. P2 indica o formato PGM */
    scanf("%s ", nome_formato);
    if (strcmp(nome_formato, "P2") != 0)
        return 0;
    
    /* Le o '#', que indica um comentario, e os numeros indicando
     *      o filtro e os parametros, se houver */
    scanf("# %d", F);
    
    if (*F == 1) {
        scanf("%lf %lf", C, Gama);
    }
    
    /* Le dimensoes e intensidade maxima da imagem */
    scanf("%d", W);
    scanf("%d", H);
    scanf("%d", MaxV);
    
    /* Le o valor de cada ponto da imagem */
    for (i = 0; i < (*H); i++) {
        for (j = 0; j < (*W); j++) {
            scanf("%d", &img[i][j]);
        }
    }
    
    return 1;
}

/* Escreve a imagem em formato PGM na saida padrao */
void escrever_pgm(int img[][MAX_TAM], int W, int H, int MaxV) {
    int i, j;
    
    /* Escreve os atributos da imagem */
    /* Tipo da imagem: P2 significa pgm*/
    printf("P2\n");
    
    /* Dimensoes e intensidade maxima da imagem */
    printf("%d %d %d\n", W, H, MaxV);
    
    /* Escreve os pontos da imagem */
    for (i = 0; i < H; i++) {
        printf("%d", img[i][0]);
        for (j = 1; j < W; j++) {
            printf(" %d", img[i][j]);
        }
        printf("\n");
    }
}

/* Transformacao de Potencia (gama) */
void potencia(int img[][MAX_TAM], int W, int H, int MaxV, 
              double c, double gama) {
    
    int i, j;
    
    for(i = 0; i < H; i++)
    {
        for(j = 0; j < W; j++)
        {
            /*Caso o valor do pixel seja maior que MaxV, faz com que ele receba 
            o valor MaxV*/
            if(floor(c * pow(img[i][j], gama)) > MaxV)
            {
                img[i][j] = MaxV;
            }
            /*Caso o valor do pixel seja menor que 0, faz com que ele receba o 
            valor 0*/
            else if(floor(c * pow(img[i][j], gama)) < 0 )
            {
                img[i][j] = 0;
            }
            else
            {
                img[i][j] = floor(c * pow(img[i][j], gama));
            }
        }
    }
}

/* Espelhamento */
void espelhamento(int img[][MAX_TAM], int W, int H) {
    
    int i, j, k, l;
    
    /*Copia o valor do pixel do lado direito da imagem, na posicao 
    correspondente no lado esquerdo dela*/
    for(i = 0, k = 0; i < H; i++, k++)
    {
        for(j = W - 1, l = 0; j >= W / 2; j--, l++)
        {
            img[k][l] = img[i][j];
        }
    }
}
              
/* Reducao de Ruidos com Filtro Gaussiano */
void reducaoRuido(int img[][MAX_TAM], int W, int H, int MaxV) {
    
    int i, j;
    float img2[MAX_TAM][MAX_TAM];
    
    /*Copia a matriz imagem em uma matriz auxiliar para realizar as 
    modificacoes*/
    for(i = 0; i < H; i++)
    {
        for(j = 0; j < W; j++)
        {
            img2[i][j] = 0;
        }
    }
    
    for(i = 0, j = 0; i < H - 2; i++, j = 0)
    {
        for(j = 0; j < W - 2; j++)
        {
            /*Realiza as modificacoes correspondentes as posicoes verticais e 
            horizontais da vizinhanca do pixel*/
            img2[i + 1][j + 1] += ((2 * (float)img[i][j + 1]) / 16);
            img2[i + 1][j + 1] += ((2 * (float)img[i + 2][j + 1]) / 16);
            img2[i + 1][j + 1] += ((2 * (float)img[i + 1][j]) / 16); 
            img2[i + 1][j + 1] += ((2 * (float)img[i + 1][j + 2]) / 16);
            
            /*Realiza as modificacoes correspondentes as posicoes diagonais da 
            vizinhanca do pixel*/
            img2[i + 1][j + 1] += ((1 * (float)img[i][j]) / 16);
            img2[i + 1][j + 1] += ((1 * (float)img[i + 2][j]) / 16);
            img2[i + 1][j + 1] += ((1 * (float)img[i][j + 2]) / 16);
            img2[i + 1][j + 1] += ((1 * (float)img[i + 2][j + 2]) / 16);
            
            /*Realiza as modificacoes correspondentes a posicao do pixel*/
            img2[i + 1][j + 1] += ((4 * (float)img[i + 1][j + 1]) / 16);
            
            /*Transforma os resultados obtidos nas modificacoes, em numeros 
            inteiros*/
            img2[i + 1][j + 1] = floor(img2[i + 1][j + 1]);
        }
    }
    
    /*Passa para a matriz imagem, a matriz auxiliar modificada*/ 
    for(i = 1; i < H - 1; i++)
    {
        for(j = 1; j < W - 1; j++)
        {
            img[i][j] = img2[i][j];
        }
    }             
}
              
/* Rotacao 90 graus */
void rotacao(int img[][MAX_TAM], int W, int H) {
    
    int i, j, k, l, img2[MAX_TAM][MAX_TAM];
    
    /*Copia a matriz imagem em uma matriz auxiliar para realizar as 
    modificacoes*/
    for(i = 0; i < H; i++)
    {
        for(j = 0; j < W; j++)
        {
            img2[i][j] = img[i][j];
        }
    }
    
    /*Copia os pixels da matriz auxiliar, na matriz imagem, colocando-os nas 
    posicoes correspondentes para a rotacao da imagem, trocando o numero de 
    linhas pelo numero de colunas e o numero de colunas pelo numero de linhas*/
    for(i = 0, k = 0; k < H; i++, k++)
    {
        for(j = 0, l = W - 1; l >= 0; j++, l--)
        {
            img[l][k] = img2[i][j];
        }
    }
}
              
int main() {
    /* Matriz que armazena os pixels da imagem */
    int img[MAX_TAM][MAX_TAM];
    /* Atributos da imagem */
    int W, H, MaxV, aux;
    /* Identificador do filtro a ser utilizado */
    int F;
    /* Parametros a serem passados para a potencia */
    double C, Gama;
                  
    /* Le a imagem */
    if (ler_pgm(img, &W, &H, &MaxV, &F, &C, &Gama) != 1) {
        printf("Error: nao foi possivel ler a imagem\n");
        return 0;
    }
                  
    /* Seleciona o filtro */
    switch (F) {
        case 1:
            potencia(img, W, H, MaxV, C, Gama);
            break;
        case 2:
            espelhamento(img, W, H);
            break;
        case 3:
            reducaoRuido(img, W, H, MaxV);
            break;
        case 4:
            rotacao(img, W, H);
            aux = W;
            W = H;
            H = aux;
            break;
    }
                  
    /* Escreve a imagem */
    escrever_pgm(img, W, H, MaxV);
                  
    return 0;
}