@ Este codigo le um valor da entrada padrao, calcula o e-nesimo elemento de Fibonacci e
@ imprime o resultado na saida padrao.
@ O numero de elementos da sequencia de Fibonacci sera recebido da entrada padrao na forma binaria.
@ O valor binario devera conter EXATAMENTE 16 digitos. 
@   ex:  2  = 0000000000000010
@
@ A resposta da entrada (o seu dobro) sera mostrado na saida padrao tambem no formato de 
@ uma string binaria de 16 digitos.
@

.text                         @ Muda o ponto de montagem para a secao de codigo (text)

.globl _start                 @ torna o rotulo _start global, ou seja, visivel pelo ligador.

.align 4                      @ Alinha a posicao atual de montagem em um endereco multiplo de 4
_start:                       @ ponto de entrada do programa.

@ -- le uma sequencia de 16 bytes da entrada padrao
@ -- e armazena no buffer identificado pelo rotulo string.

mov r0, #0            @ carrega o valor 0 em r0, indicando que a entrada da
@ syscall read sera em stdin
ldr r1, =string       @ carrega em r1 o endereco de um buffer na memoria.
mov r2, #17           @ carrega em r2 a quantidade maxima de dados (em bytes) a se lida.
@ r0, r1 e r2 serao os argumentos da syscall read
mov r7, #3            @ carrega o valor 3 para r7, indicando o tipo da syscall (read)
svc 0x0               @ realiza uma chamada de sistema (syscall)

@ -- converte a sequencia de caracteres lida em um numero na representacao sem sinal.

mov  r0, #0           @ para armazenar valor convertido
ldr  r1, =string      @ carrega em r1 o endereco da string
mov  r2, #0           @ iterador de loop

loop_c:
mov  r0, r0, LSL #1   @ desloca o valor de r0 para esquerda 
@ LSB (bit menos significativo) de r0 recebe 0 
ldrb r3, [r1, r2]     @ r3 = string[r2]
cmp  r3, #49          @ compara r3 com '1'  (49 em ASCII)
blt  skip             @ se for menor: r0 ja esta com 0 no LSB
orr  r0, r0, #1       @ senao: LSB de r0 recebe 1
skip:
add r2, r2, #1        @ incrementa variavel de controle da iteracao
cmp r2, #16           @ compara r2 com o tamanho da string binaria
blt loop_c            @ se ainda esta com um valor menor que o tamanho da string

@ -- Calcula o e-nesimo elemento da sequencia de Fibonacci
mov r8, #0    @a (n - 2)
mov r9, #1    @b (n - 1)
mov r10, #0   @i variavel que armazena o iterador

@Caso n == 0, retorna 0
cmp r0, #0
beq fim_fibonacci
    
@Caso n != 0, realiza as iteracoes

@n = n - 1
sub r0, #1

loop_fib:
    cmp r10, r0         @Compara i com n
    bhs fim_loop        @if i >= n, sai do loop
    mov r11, r8         @Utiliza um registrador auxiliar para armazenar o valor de a
    mov r8, r9          @a = b
    add r9, r11, r8     @b = aux + b
    add r10, #1         @incrementa o iterador
    b loop_fib
fim_loop:
    mov r0, r9          @move o resultado em b, para o registrador r0, que ira imprimir o resultado

fim_fibonacci:

@ -- converte o resultado (em r0) em uma sequencia de caracteres '0' e '1' no buffer string.

ldr r1, =string       @ string  para preencher com string binaria
mov r2, #15           @ contador de iteracao
mov r3, #1            @ valor para shift

loop:
mov r4, #49           @ r4 = '1'    
and r5, r0, r3        @ r5 = r0 AND r3
cmp r5, #0            @ compara r5 com 0 (zero)
bgt one               @ se for maior: r4 ja esta com '1'
mov r4, #48           @ senao: r4 = '0'
one:
strb r4, [r1, r2]     @ string[r2] = r4
sub  r2, r2, #1       @ decrementa a variavel de controle do laco
mov  r3, r3, LSL #1   @ r3 = r3 << 1
cmp  r2, #0           @ compara r com zero
bge  loop             @ se ainda e maior ou igual, volta para o loop

@ -- escreve a sequencia de 16 bytes na saida padrao.

mov r0, #1            @ carrega o valor 1 em r0, indicando que a saida da
@ syscall write sera em stdout
ldr r1, =string       @ carrega em r1 o endereco da string
mov r2, #17           @ carrega em r2 o tamanho da string. r0,r1 e r2 serao
@ os argumentos da syscall write
mov r7, #4            @ carrega o valor 4 para r7, indica o tipo da syscall
svc 0x0               @ realiza uma chamada de sistema (syscall)

mov r7, #1            @ carrega o valor 1 em r7, indicando a escolha da
@ syscall exit
svc 0x0         

.data @ Muda o ponto de montagem para a secao de dados


string:	.asciz "0000000000000000\n"  @ a diretiva .asciz coloca a cadeia
@ de caracteres especificada como parametro
@ na memoria e concatena o valor zero, indicando
@ o termino da cadeia.
