.globl _start

.data

input_buffer:   .skip 32
output_buffer:  .skip 32
    
.text
.align 4

@ Funcao inicial
_start:

    @Realiza as operacoes de encode
    
    @ Chama a funcao "read" para ler 4 caracteres da entrada padrao
    ldr r0, =input_buffer
    mov r1, #5             @ 4 caracteres + '\n'
    bl  read
    mov r4, r0             @ copia o retorno para r4.

    @ Chama a funcao "atoi" para converter a string para um numero
    ldr r0, =input_buffer
    mov r1, r4
    bl  atoi

    @ Chama a funcao "encode" para codificar o valor de r0 usando
    @ o codigo de hamming.
    bl  encode
    mov r4, r0             @ copia o retorno para r4.
	
    @ Chama a funcao "itoa" para converter o valor codificado
    @ para uma sequencia de caracteres '0's e '1's
    ldr r0, =output_buffer
    mov r1, #7
    mov r2, r4
    bl  itoa

    @ Adiciona o caractere '\n' ao final da sequencia (byte 7)
    ldr r0, =output_buffer
    mov r1, #'\n'
    strb r1, [r0, #7]

    @ Chama a funcao write para escrever os 7 caracteres e
    @ o '\n' na saida padrao.
    ldr r0, =output_buffer
    mov r1, #8         @ 7 caracteres + '\n'
    bl  write
    
    @Realiza as operacoes de decode
    
    @ Chama a funcao "read" para ler 7 caracteres da entrada padrao
    ldr r0, =input_buffer
    mov r1, #8             @ 7 caracteres + '\n'
    bl  read
    mov r4, r0             @ copia o retorno para r4.
    
    @ Chama a funcao "atoi" para converter a string para um numero
    ldr r0, =input_buffer
    mov r1, r4
    bl  atoi
    
    @ Chama a funcao "decode" para decodificar o valor de r0 usando
    @ o codigo de hamming.
    bl  decode
    mov r4, r0             @ copia o retorno para r4.
    mov r5, r1             @ copia o retorno para r5
    
    @ Chama a funcao "itoa" para converter o valor codificado
    @ para uma sequencia de caracteres '0's e '1's
    ldr r0, =output_buffer
    mov r1, #4
    mov r2, r4
    bl  itoa
    
    @ Adiciona o caractere '\n' ao final da sequencia (byte 4)
    ldr r0, =output_buffer
    mov r1, #'\n'
    strb r1, [r0, #4]
    
    @ Chama a funcao write para escrever os 4 caracteres e
    @ o '\n' na saida padrao.
    ldr r0, =output_buffer
    mov r1, #5         @ 4 caracteres + '\n'
    bl  write
   
    @Imprime se houve erro na codificacao 
    
    @ Chama a funcao "itoa" para converter o valor codificado
    @ para uma sequencia de caracteres '0's e '1's
    ldr r0, =output_buffer
    mov r1, #1
    mov r2, r5
    bl  itoa
    
    @ Adiciona o caractere '\n' ao final da sequencia (byte 1)
    ldr r0, =output_buffer
    mov r1, #'\n'
    strb r1, [r0, #1]
    
    @ Chama a funcao write para escrever o caractere de erro e
    @ o '\n' na saida padrao.
    ldr r0, =output_buffer
    mov r1, #2         @ 1 caractere + '\n'
    bl  write
    
    @ Chama a funcao exit para finalizar processo.
    mov r0, #0
    bl  exit

@ Codifica o valor de entrada usando o codigo de hamming.
@ parametros:
@  r0: valor de entrada (4 bits menos significativos)
@ retorno:
@  r0: valor codificado (7 bits como especificado no enunciado).
encode:    
       push {r4-r11, lr}
       
       @Armazena os valores de d1(r4), d2(r3), d3(r2), d4(r1)
       
       @r1 (0001) - d4
       and r1, r0, #0b00000001
       
       @r2(0010) - d3
       and r2, r0, #0b00000010
       mov r2, r2, lsr #1
       
       @r3(0100) - d2
       and r3, r0, #0b00000100
       mov r3, r3, lsr #2
       
       @r4(1000) - d1
       and r4, r0, #0b00001000
       mov r4, r4, lsr #3
       
       @Verifica a paridade p1
       eor r5, r4, r3
       eor r5, r5, r1
       mov r5, r5, lsl #6
       
       @Verifica a paridade p2
       eor r6, r4, r2
       eor r6, r6, r1
       mov r6, r6, lsl #5
       
       @Verifica a paridade p3
       eor r7, r3, r2
       eor r7, r7, r1
       mov r7, r7, lsl #3
       
       @Armazena o resultado codificado em r0
       
       mov r0, #0
       
       @Armazena d4
       add r0, r1
       
       @Armazena d3
       add r0, r2, lsl #1
       
       @Armazena d2
       add r0, r3, lsl #2
       
       @Armazena p3
       add r0, r7
       
       @Armazena d1
       add r0, r4, lsl #4
       
       @Armazena p2
       add r0, r6
       
       @Armazena p1
       add r0, r5
       
       pop  {r4-r11, lr}
       mov  pc, lr

@ Decodifica o valor de entrada usando o codigo de hamming.
@ parametros:
@  r0: valor de entrada (7 bits menos significativos)
@ retorno:
@  r0: valor decodificado (4 bits como especificado no enunciado).
@  r1: 1 se houve erro e 0 se nao houve.
decode:    
       push {r4-r11, lr}
       
       @Armazena os valores de d1(r5), d2(r4), d3(r3), d4(r2)
       
       @r2 (0001) - d4
       and r2, r0, #0b00000001
       
       @r3 (0010) - d3
       and r3, r0, #0b00000010
       
       @r4 (0100) - d2
       and r4, r0, #0b00000100
       
       @r5 (10000) - d1
       and r5, r0, #0b00010000
       
       @Armazena os valores de p1(r6), p2(r7), p3(r8)
       
       @p1
       and r6, r0, #0b01000000
       mov r6, r6, lsr #6
       
       @p2
       and r7, r0, #0b00100000
       mov r7, r7, lsr #5
       
       @p3
       and r8, r0, #0b00001000
       mov r8, r8, lsr #3
       
       @Armazena em r0, o valor decodificado
       mov r0, #0
       add r0, r2
       add r0, r3
       add r0, r4
       add r0, r5, lsr #1
       
       @Desloca para o bit menos significativo os valores de d1, d2, d3
       mov r3, r3, lsr #1
       mov r4, r4, lsr #2
       mov r5, r5, lsr #4
       
       @Aplica o XOR para verificar as paridades p1(r6), p2(r7) e p3(r8)
       
       @Verifica p1
       mov r9, #0
       eor r9, r5, r4
       eor r9, r9, r2
       eor r1, r9, r6
       cmp r1, #1
       beq erro
       
       @Verifica p2
       mov r10, #0
       eor r10, r5, r3
       eor r10, r10, r2
       eor r1, r10, r7
       cmp r1, #1
       beq erro
       
       @Verifica p3
       mov r11, #0
       eor r11, r4, r3
       eor r11, r11, r2
       eor r1, r11, r8
       cmp r1, #1
       beq erro
       
erro:
       pop  {r4-r11, lr}
       mov  pc, lr

@ Le uma sequencia de bytes da entrada padrao.
@ parametros:
@  r0: endereco do buffer de memoria que recebera a sequencia de bytes.
@  r1: numero maximo de bytes que pode ser lido (tamanho do buffer).
@ retorno:
@  r0: numero de bytes lidos.
read:
    push {r4,r5, lr}
    mov r4, r0
    mov r5, r1
    mov r0, #0         @ stdin file descriptor = 0
    mov r1, r4         @ endereco do buffer
    mov r2, r5         @ tamanho maximo.
    mov r7, #3         @ read
    svc 0x0
    pop {r4, r5, lr}
    mov pc, lr

@ Escreve uma sequencia de bytes na saida padrao.
@ parametros:
@  r0: endereco do buffer de memoria que contem a sequencia de bytes.
@  r1: numero de bytes a serem escritos
write:
    push {r4,r5, lr}
    mov r4, r0
    mov r5, r1
    mov r0, #1         @ stdout file descriptor = 1
    mov r1, r4         @ endereco do buffer
    mov r2, r5         @ tamanho do buffer.
    mov r7, #4         @ write
    svc 0x0
    pop {r4, r5, lr}
    mov pc, lr

@ Finaliza a execucao de um processo.
@  r0: codigo de finalizacao (Zero para finalizacao correta)
exit:    
    mov r7, #1         @ syscall number for exit
    svc 0x0

@ Converte uma sequencia de caracteres '0' e '1' em um numero binario
@ parametros:
@  r0: endereco do buffer de memoria que armazena a sequencia de caracteres.
@  r1: numero de caracteres a ser considerado na conversao
@ retorno:
@  r0: numero binario
atoi:
    push {r4, r5, lr}
    mov r4, r0         @ r4 == endereco do buffer de caracteres
    mov r5, r1         @ r5 == numero de caracteres a ser considerado 
    mov r0, #0         @ number = 0
    mov r1, #0         @ loop indice
atoi_loop:
    cmp r1, r5         @ se indice == tamanho maximo
    beq atoi_end       @ finaliza conversao
    mov r0, r0, lsl #1 
    ldrb r2, [r4, r1]  
    cmp r2, #'0'       @ identifica bit
    orrne r0, r0, #1   
    add r1, r1, #1     @ indice++
    b atoi_loop
atoi_end:
    pop {r4, r5, lr}
    mov pc, lr

@ Converte um numero binario em uma sequencia de caracteres '0' e '1'
@ parametros:
@  r0: endereco do buffer de memoria que recebera a sequencia de caracteres.
@  r1: numero de caracteres a ser considerado na conversao
@  r2: numero binario
itoa:
    push {r4, r5, lr}
    mov r4, r0
itoa_loop:
    sub r1, r1, #1         @ decremento do indice
    cmp r1, #0          @ verifica se ainda ha bits a serem lidos
    blt itoa_end
    and r3, r2, #1
    cmp r3, #0
    moveq r3, #'0'      @ identifica o bit
    movne r3, #'1'
    mov r2, r2, lsr #1  @ prepara o proximo bit
    strb r3, [r4, r1]   @ escreve caractere na memoria
    b itoa_loop
itoa_end:
    pop {r4, r5, lr}
    mov pc, lr    
