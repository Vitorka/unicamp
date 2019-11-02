.org 0x0
.section .iv,"a"


_start:


interrupt_vector:
    b RESET_HANDLER
.org 0x08
    b SYSCALL_HANDLER
.org 0x18
    b IRQ_HANDLER

.org 0x100
.text

RESET_HANDLER:

    @ Zera o contador
    ldr r2, =SYSTEM_TIME  @lembre-se de declarar esse contador em uma secao de dados!
    mov r0,#0
    str r0,[r2]

    @Zera o contador de alarmes
    ldr r1, =ALARMS_COUNTER
    mov r2, #0
    str r2, [r1]

    @Set interrupt table base address on coprocessor 15.
    ldr r0, =interrupt_vector
    mcr p15, 0, r0, c12, c0, 0

    @Zera o vetor de alarmes
    ldr r0, =ARRAY_TIME_ALARMS
    ldr r1, =ARRAY_POSITION_FUNCTIONS

    mov r2, #0
    mov r3, #0
    zera_loop:
      str r3, [r0], #4
      str r3, [r1], #4
      add r2, r2, #1
      cmp r2, #8
      bls zera_loop

SET_DIST_INTERVAL:

    .set DIST_INTERVAL, 1

SET_TIME_SZ:

    .set TIME_SZ, 50

@Posicao inicial de memoria do programa do usuario
SET_PROGRAM_USER_POSITION:

    .set PROGRAM_USER, 0x77802000

@Posicao inicial de memoria das stacks de usuario e supervisor
SET_STACK_POSITIONS:

    .set STACK_USER, 0x7fffffff
    .set STACK_SUPERVISOR, 0x7effffff
    .set STACK_IRQ, 0x7dffffff

SET_GPIO:

    @ constantes para os endereços do SET_GPIO
    .set GPIO_BASE, 0x53F84000
    .set GPIO_DR, 0x00
    .set GPIO_GDIR, 0x04
    .set GPIO_PSR, 0x08

    @ Setando o GPIO_GDIR
    msr CPSR_c, #0x13
    ldr r0, =0b11111111111111000000000000111110
    ldr r1, =GPIO_BASE
    str r0, [r1, #GPIO_GDIR]

SET_GPT:

    @ constantes para os endereços do GPT
    .set GPT_BASE, 0x053FA0000
    .set GPT_CR, 0x0
    .set GPT_PR, 0x04
    .set GPT_SR, 0x08
    .set GPT_IR, 0x0C
    .set GPT_OCR1, 0x10

    ldr r1, =GPT_BASE

    @Colocando o valor 0x041 em GPT_CR
    mov r0, #0x41
    str r0, [r1, #GPT_CR]

    @Zerando GPT_PR
    mov r0, #0
    str r0, [r1, #GPT_PR]

    @Colocando em GPT_OCR1 o valor que se quer contar (100)
    ldr r0, =TIME_SZ
    str r0, [r1, #GPT_OCR1]

    @Gravando 1 no registrador GPT_IR
    mov r0, #1
    str r0, [r1, #GPT_IR]

SET_TZIC:
    @ Constantes para os enderecos do TZIC
    .set TZIC_BASE,             0x0FFFC000
    .set TZIC_INTCTRL,          0x0
    .set TZIC_INTSEC1,          0x84
    .set TZIC_ENSET1,           0x104
    .set TZIC_PRIOMASK,         0xC
    .set TZIC_PRIORITY9,        0x424


    @ Liga o controlador de interrupcoes
    @ R1 <= TZIC_BASE


    ldr	r1, =TZIC_BASE


    @ Configura interrupcao 39 do GPT como nao segura
    mov	r0, #(1 << 7)
    str	r0, [r1, #TZIC_INTSEC1]


    @ Habilita interrupcao 39 (GPT)
    @ reg1 bit 7 (gpt)


    mov	r0, #(1 << 7)
    str	r0, [r1, #TZIC_ENSET1]


    @ Configure interrupt39 priority as 1
    @ reg9, byte 3


    ldr r0, [r1, #TZIC_PRIORITY9]
    bic r0, r0, #0xFF000000
    mov r2, #1
    orr r0, r0, r2, lsl #24
    str r0, [r1, #TZIC_PRIORITY9]


    @ Configure PRIOMASK as 0
    eor r0, r0, r0
    str r0, [r1, #TZIC_PRIOMASK]


    @ Habilita o controlador de interrupcoes
    mov	r0, #1
    str	r0, [r1, #TZIC_INTCTRL]

    msr CPSR_c, #0x13           @Seta o modo SUPERVISOR
    ldr sp, =STACK_SUPERVISOR   @Aponta o inicio da STACK_SUPERVISOR

    msr CPSR_c, #0x12
    ldr sp, =STACK_IRQ

    @Configura as STACKS
    msr  CPSR_c, #0x10          @Seta o modo USER
    ldr sp, =STACK_USER         @Aponta o inicio da STACK_USER

    @Apos configurar os registradores, salta para o programa do usuario
    ldr pc, =PROGRAM_USER

IRQ_HANDLER:

    push {r0-r12, lr}                  @Salva todos os registradores

    @Liga o controlador de interrupcoes
    ldr r1, =GPT_BASE

    @Configura GPT_SR
    mov r0, #0x1
    str r0, [r1, #GPT_SR]

    @Adiciona um ao contador do tempo do sistema
    ldr r2, =SYSTEM_TIME
    ldr r0, [r2]
    add r0, r0, #1
    str r0, [r2]

    @incrementa COUNTER_DIST_INTERVAL
    ldr r0, =COUNTER_DIST_INTERVAL    @Coloca em r0 o endereco de COUNTER_DIST_INTERVAL
    ldr r1, [r0]                      @Coloca em r1 o valot de COUNTER_DIST_INTERVAL
    add r1, r1, #1                    @Adiciona unm a r1
    str r1, [r0]                      @Atualiza o valor de COUNTER_DIST_INTERVAL

    @Verifica se existem alarmes a serem verificados
    ldr r0, =ALARMS_COUNTER           @Coloca em r0 a posicao do contador de alarmes
    ldr r0, [r0]                      @Coloca em r0 o numero de alarmes existentes
    cmp r0, #0                        @Compara o numero de alarmes com zero
    blhi VERIFICA_ALARMES             @Salta para a funcao que verifica a lista de alarmes

    @Verifica se existem callbacks a serem verificadas
    ldr r0, =PROX_COUNTER             @Coloca em r0 a posicao do contador de callbacks
    ldr r0, [r0]                      @Coloca em r0 o numero de callbacks existentes
    cmp r0, #0                        @Compara o numero de callbacks com zero
    beq fim_irq                       @Caso nao existam callbacks a serem verificadas, pula para o final da IRQ_HANDLER
    ldr r0, =COUNTER_DIST_INTERVAL    @Coloca em r0 a posicao do contador de DIST_INTERVAL
    ldr r0, [r0]                      @Coloca em r0 o valor de COUNTER_DIST_INTERVAL
    ldr r1, =DIST_INTERVAL            @Coloca em r1 o valor de DIST_INTERVAL
    cmp r0, r1                        @Compara COUNTER_DIST_INTERVAL e DIST_INTERVAL
    bleq VERIFICA_CALLBACKS           @Caso existam callbacks e o DIST_INTERVAL tenha sido atingido, salta para a funcao que verifica as callbacks

    fim_irq:
    pop {r0-r12, lr}                  @Recupera todos os registradores salvos
    sub lr, lr, #4                    @Ajeita o lr
    movs pc, lr                       @Retorna para o programa do ususario

VERIFICA_ALARMES:

    push {r0-r12, lr}                 @Salva todos os registradores

    @Recupera o inicio dos vetores de tempo e funcoes
    ldr r0, =ARRAY_POSITION_FUNCTIONS @Coloca em r0 o inicio do vetor de funcoes
    ldr r1, =ARRAY_TIME_ALARMS        @Coloca em r1 o inicio do vetor de tempos dos alarmes

    @Percorre o vetor de funcoes para trata-los
    ldr r3, =SYSTEM_TIME              @Coloca em r3 o endereco do tempo do sistema
    ldr r3, [r3]                      @Coloca em r3 o tempo do sistema
    mov r5, #8                        @Coloca em r5 o numero de alarmes que devem ser verificados
    mov r6, #0                        @Contador para verificar se todos os alarmes ja foram verificados

    loop_verificacoes:
      ldr r2, [r1]                    @Coloca em r2 o tempo do alarme
      ldr r4, [r0]                    @Coloca em r4 o endereco da funcao que deve ser executada
      cmp r4, #0                      @Compara para ver se o valor do alarme adicionado e zero
      beq fim                         @Se for zero, pula para o fim do loop de verificacoes
      cmp r2, r3                      @Compara o tempo do alarme com o tempo do sistema

      @Zera os vetores caso o alarme tenha sido atendido
      mov r9, #0                      @Coloca em r9 o valor zero para zerar as posicoes no vetor de tempos e funcoes
      strls r9, [r0]                  @Zera a posicao do vetor da funcao que ja foi utilizada
      strls r9, [r1]                  @Zera a posicao do vetor do tempo de alarme que ja foi utilizado
      ldr r10, =ALARMS_COUNTER        @Coloca em r10 o endereco de ALARMS_COUNTER
      ldr r11, [r10]                  @Coloca em r11 o valor de ALARMS_COUNTER
      sub r11, r11, #1                @Subtrai um do ALARMS_COUNTER
      strls r11, [r10]                @Altera o valor de ALARMS_COUNTER
      mrs r8, spsr                    @Salva o spsr
      push {r0-r12, lr}               @Salva todos os registradores no modo IRQ
      msr CPSR_c, #0x10               @Muda para o modo USUARIO
      push {r0-r12, lr}               @Salva todos os registradores do modo USUARIO
      blxls r4                        @Caso o tempo do alarme tenha sido atingido, pula para a funcao que deve ser executada
      pop {r0-r12, lr}                @Recupera todos os registradores do modo USUARIO
      mov r7, #23                     @Coloca em r7 o valor da syscall especial para retornar para o modo IRQ
      ldr r8, =retorno                @Coloca em r8 o endereco do rotulo para o qual ele deve retornar
      svc 0x0                         @Realiza uma interrupcao de software

      @Retorna para o modo IRQ
      retorno:
      msr CPSR_c, #0xD2               @Muda para o modo IRQ
      pop {r0-r12, lr}                @Recupera todos os registradores
      msr spsr, r8                    @Recupera spsr

      fim:
      add r6, r6, #1                  @Conta um no registrador que conta quantos alarmes ja foram verificados
      cmp r6, r5                      @Compara o numero de alarmes verificados com o numero de alarmes adicionados
      add r0, r0, #4                  @Pula para a proxima posicao do vetor de funcoes
      add r1, r1, #4                  @Pula para a proxima posicao do vetor de tempos de alarme
      blo loop_verificacoes           @Caso nem todos os alarmes tenham sido verificados, pula para o inicio do laco

    pop {r0-r12, lr}                  @Recupera todos os registradores e retorna para IRQ_HANDLER
    mov pc, lr

VERIFICA_CALLBACKS:

      push {r0-r12, lr}                   @Salva todos os registradores

      @Recupera o inicio dos vetores de id dos motores, de limiar de distancia e funcoes
      ldr r1, =ARRAY_ID_PROX              @Coloca em r1 o inicio do vetor de IDS
      ldr r2, =ARRAY_DIST_PROX            @Coloca em r2 o inicio do vetor de limiar de distancias
      ldr r3, =ARRAY_POSITION_PROX        @Coloca em r3 o inicio do vetor de funcoes

      ldr r11, [r3]

      mov r10, #0                         @Coloca em r10 o contador de callbacks verificadas
      ldr r9, =PROX_COUNTER               @Coloca em r9 o endereco do contador de callbacks
      ldr r9, [r9]                        @Coloca em r9 o numero de callbacks adicionadas
      loop_verifica_callbacks:
        push {r1-r12, lr}                 @Salva todos os registradores no modo IRQ
        msr CPSR_c, #0x1F                 @Muda para o modo SYSTEM para poder empilhar o id
        ldr r4, [r1]                      @Coloca em r4 o id do radar que deve ser verificado
        push {r4, lr}                     @Coloca na pilha do USUARIO o id do radar que deve ser verificado
        msr CPSR_c, #0x13                 @Muda para o modo SUPERVISOR
        push {lr}                         @Salva todos os registradores no modo SUPERVISOR
        bl READ_SONAR                     @Salta para a funcao READ_SONAR para verificar a distancia lida pelo sonar requerido
        pop {r4, lr}                      @Desempilha o que foi empilhado em modo USUARIO

        @Retorna para o modo IRQ
        mov r7, #23                       @Coloca em r7 o valor da syscall especial para retornar para o modo IRQ
        ldr r8, =retorno_loop_callback    @Coloca em r8 o endereco do rotulo para o qual ele deve retornar
        svc 0x0

        retorno_loop_callback:
        pop {lr}                          @Recupera todos os registradores no modo SUPERVISOR
        msr CPSR_c, #0xD2                 @Muda para o modo IRQ
        pop {r1-r12, lr}                  @Recupera todos os registradores no modo IRQ
        ldr r5, [r2]                      @Coloca em r5 o limiar de distancia que deve ser respeitado
        ldr r6, [r3]                      @Coloca em r6 o endereco da funcao que deve ser chamada
        cmp r0, r5                        @Compara o valor obtido pelo radar, com o limiar
        push {r1-r12, lr}                 @Salva todos os registradores no modo IRQ
        msr CPSR_c, #0x10                 @Muda para o modo USUARIO
        push {r0-r12, lr}                 @Salva todos os registradores do modo USUARIO
        blxlo r6                          @Caso a distancia lida seja menor do que o limiar, salta para a funcao
        pop {r0-r12, lr}                  @Recupera todos os registradores do modo USUARIO

        @Retorna para o modo IRQ
        mov r7, #23                       @Coloca em r7 o valor da syscall especial para retornar para o modo IRQ
        ldr r8, =retorno_callbak          @Coloca em r8 o endereco do rotulo para o qual ele deve retornar
        svc 0x0                           @Realiza uma interrupcao de software
        retorno_callbak:
        msr CPSR_c, #0xD2                 @Muda para o modo IRQ
        pop {r1-r12, lr}                  @Recupera todos os registradores no modo IRQ

        @Atualiza posicoes
        add r10, r10, #1                  @Adiciona um ao contador de callbacks verificadas
        add r1, r1, #4                    @Pula para a proxima posicao do vetor de ids
        add r2, r2, #4                    @Pula para a proxima posicao do vetor de limiar de distancias
        add r3, r3, #4                    @Pula para a proxima posicao do vetor de funcoes
        cmp r10, r9                       @Compara o numero de callbacks verificadas com o numero de calbacks totais existentes
        blo loop_verifica_callbacks       @Caso nao tenha verificado todas as callbacks, retorna ao inicio do loop

      ldr r0, =COUNTER_DIST_INTERVAL      @Recupera em r0 o endereco do contador de tempos de sistema para atingir o DIST_INTERVAL
      mov r1, #0                          @Coloca em r1 0 valor zero pra adicionar em COUNTER_DIST_INTERVAL
      str r1, [r0]                        @Salva o valor zerado de COUNTER_DIST_INTERVAL

      pop {r0-r12, lr}                    @Recupera todos os registradores
      mov pc, lr                          @Retorna para IRQ_HANDLER

SYSCALL_HANDLER:

    @ compara r7 com o numero das syscalls
    @ Códigos syscalls:
    @ read_sonar: código = 16
    @ register_proximity_callback: código = 17
    @ set_motor_speed: código = 18
    @ set_motors_speed: código = 19
    @ get_time: código = 20
    @ set_time: código = 21
    @ set_alarm: código = 22
    cmp r7, #16
    beq READ_SONAR
    cmp r7, #17
    beq REGISTER_PROXIMITY_CALLBACK
    cmp r7, #18
    beq SET_MOTOR_SPEED
    cmp r7, #19
    beq SET_MOTORS_SPEED
    cmp r7, #20
    beq GET_TIME
    cmp r7, #21
    beq SET_TIME
    cmp r7, #22
    beq SET_ALARM
    cmp r7, #23
    bxeq r8

SET_MOTOR_SPEED:

    push {r1-r12, lr}       @Salva todos os registradores
    msr CPSR_c, #0x1F       @Ativa o modo SYSTEM

    ldr r0, [sp]            @Recupera o parametro 1: id_motor
    ldr r1, [sp, #4]        @Recupera o parametro 2: speed_motor

    @Trata erros
    msr CPSR_c, #0x13       @Ativa o modo SUPERVISOR
    cmp r0, #1              @Compara com 1 para ver se o sonar eh valido
    bhi RETURN_ERROR1
    cmp r1, #36             @Compara com 36 para ver se a velocidade eh valida
    bhi RETURN_ERROR2

    ldr r3, =GPIO_BASE      @Pega a posicao inicial do GPIO

    cmp r0, #0              @Verifica se deve mexer no motor 0
    beq SET_MOTOR_0         @Caso o id seja 0, altera o motor 0

SET_MOTOR_1:

    mov r1, r1, lsl #26     @Desloca os bits ate a posica que indica a
                                    @velocidade do motor 0

    ldr r4, =0b00000001111111111111111111111111   @Mascara de bits para zerar
                                                          @a velocidade antiga em DR

    ldr r5, [r3, #GPIO_DR]  @Recupera o valor do registrador DR

    and r5, r5, r4          @Aplica um AND para zerar o valor antigo da
                                    @velocidade do motor em DR
    orr r5, r5, r1          @Aplica um OR para setar a nova velocidade do motor

    str r5, [r3, #GPIO_DR]  @Salva em DR a velocidade do motor

    pop {r1-r12, lr}

    movs pc, lr

SET_MOTOR_0:

    mov r1, r1, lsl #19                           @Desloca os bits ate a posica que indica a
                                                  @velocidade do motor 0

    ldr r4, =0b11111110000000111111111111111111   @Mascara de bits para zerar
                                                  @a velocidade antiga em DR
    ldr r5, [r3, #GPIO_DR]                        @Recupera o valor do registrador DR

    ldr r6, [r3, #GPIO_GDIR]

    and r5, r5, r4                                @Aplica um AND para zerar o valor antigo da
                                                  @velocidade do motor em DR
    orr r5, r5, r1                                @Aplica um OR para setar a nova velocidade do motor

    str r5, [r3, #GPIO_DR]                        @Salva em DR a velocidade do motor

    mov r0, #0                                      @retorno

    pop {r1-r12, lr}

    movs pc, lr

SET_MOTORS_SPEED:

    push {r1-r12, lr}	                            @Salva todos os registradores

    @Recupera os parametros
    msr CPSR_c, #0x1F	                            @Ativa o modo SYSTEM
    ldr r0, [sp]                                  @Recupera o parametro 1: speed_motor 0
    ldr r1, [sp, #4]                              @Recupera o parametro 2: speed_motor 1

    @Tratando erros
    msr CPSR_c, #0x13                             @Ativa o modo SUPERVISOR

    cmp r0, #36                                   @Compara com 36 para ver se a vel eh valida
    bhi RETURN_ERROR1                             @erro
    cmp r1, #36                                   @Compara com 36 para ver se a vel eh valida
    bhi RETURN_ERROR2                             @Erro

    ldr r2, =GPIO_BASE	                          @Coloca em r2 a posicao inicial do GPIO

    @Modifica as velocidades dos motores
    mov r0, r0, lsl #19	                          @Desloca os bits ate a posicao que indica a velocidade do motor 0
    mov r1, r1, lsl #26	                          @Desloca os bits ate a posicao que indica a velocidade do motor 1

    ldr r3, =0b00000000000000111111111111111111   @Mascara de bits para zerar a velocidade antiga em DR
    ldr r4, [r2, #GPIO_DR]	                      @Coloca em r4 o valor de DR
    and r4, r4, r3		                            @Aplica um AND para zerar os valores antigos das velocidades em DR

    orr r4, r4, r0		                            @Aplica um OR para setar a velocidade do motor 0
    orr r4, r4, r1		                            @Aplica um OR para setar a velocidade do motor 1

    str r4, [r2, #GPIO_DR] 	                      @Salva em DR a velocidade do motor
    mov r0, #0                                    @Retorno 0
    pop {r1-r12, lr}		                          @Recupera todos os registradores salvos
    movs pc, lr	                                  @Retorna para o programa do usuario

READ_SONAR:

    push {r1-r12, lr}                           @Salva todos os registradores

    @Recupera os parametros
    msr CPSR_c, #0xDF                           @Muda para o modo SYSTEM
    ldr r0, [sp]                                @Recupera o parametro 1: id_sonar

    @Trata erros
    cmp r0, #15
    bhi RETURN_ERROR1

    mov r0, r0, lsl #2                          @Desloca o valor de id_sonar para a posicao SONAR_MUX em DR

    msr CPSR_c, #0xD3                           @Muda para o modo SUPERVISOR

    @Realiza a leitura dos sonares
    @Recupera e modifica DR
    ldr r1, =GPIO_BASE                          @Coloca em r1 o endereco base de GPIO
    ldr r2, [r1, #GPIO_DR]                      @Coloca em r2, DR
    ldr r3, =0b11111111111111111111111111000001 @Mascara para zerar o que existia em SONAR_MUX e TRIGGER em DR
    and r2, r2, r3                              @Zera o campo SONAR_MUX em DR
    orr r2, r2, r0                              @Adiciona em r2 o id do sonar a ser lido
    str r2, [r1, #GPIO_DR]                      @Adiciona em DR o id do sonar a ser lido

    @Delay 1
    mov r4, #0
    delay1:
      add r4, r4, #1
      cmp r4, #20
      bne delay1

    rot1:
    @Modifica o TRIGGER para 1
    ldr r2, [r1, #GPIO_DR]                      @Coloca em r2, DR
    ldr r3, =0b00000000000000000000000000000010 @Mascara para setar o TRIGGER como 1
    orr r2, r2, r3                              @Seta em r2 o TRIGGER como 1
    str r2, [r1, #GPIO_DR]                      @Seta em DR o TRIGGER como 1

    @Delay 2
    mov r4, #0
    delay2:
      add r4, r4, #1
      cmp r4, #20
      bne delay2

    rot2:
    @Modifica o TRIGGER para 0
    ldr r2, [r1, #GPIO_DR]                      @Coloca em r2, DR
    ldr r3, =0b11111111111111111111111111111101 @Mascara para setar o TRIGGER como 0-
    and r2, r2, r3                              @Seta em r2 o TRIGGER como 0
    str r2, [r1, #GPIO_DR]                      @Seta em DR o TRIGGER como 0

    verifica_flag:

      @Delay 3
      mov r4, #0
      delay3:
        add r4, r4, #1
        cmp r4, #10
        bne delay3

      rot3:
      ldr r2, [r1, #GPIO_DR]                      @Coloca em r2, DR
      ldr r3, =0b00000000000000000000000000000001 @Mascara para recuperar somente o bit da FLAG
      and r2, r2, r3                              @Aplica em r2 a mascara para recuperar o bit da FLAG
      cmp r2, #1                                  @Confere se a FLAG tem valor 1
      bne verifica_flag                           @Caso nao tenha, faz a verificacao novamente

    rot4:
    ldr r2, [r1, #GPIO_PSR]                       @Coloca em r2, PSR
    mov r0, r2, lsr #6                            @Retorna em r0 o valor da distancia lida
    ldr r3, =0b00000000000000000000111111111111   @Mascara para pegar somente o vaor da distancia lida
    and r0, r0, r3

    pop {r1-r12, lr}                              @Recupera todos os registradores salvos
    movs pc, lr                                   @Retorna para o programa do usuario

SET_TIME:
    push {r1-r12, lr}	                            @Salva todos os registradores
    msr CPSR_c, #0x1F	                            @Muda para modo system
    ldr r0, [sp]	                                @Carrega em r0 o parametro que é o time a ser setado
    msr CPSR_c, #0x13	                            @Ativa modo supervisor
    ldr r1, =SYSTEM_TIME	                        @Carrega endereço de System_time em r1
    str r0, [r1]	                                @Da store do novo tempo na posicao do system_time
    pop {r1-r12, lr}
    movs pc, lr

GET_TIME:
    push {r1-r12, lr}	                            @Salva todos os registradores
    ldr r0, =SYSTEM_TIME                          @carrega em r0 a posicao do system_time
    ldr r0, [r0]	                                @Carrega novamente no proprio r0 o valor do system_time
    pop {r1-r12, lr}
    movs pc, lr

SET_ALARM:
    push {r1-r12, lr}	                  @Salva todos os registradores

    @Recupera os parametros
    msr CPSR_c, #0x1F                   @Ativa o modo SYSTEM
    ldr r0, [sp]                        @Coloca em r0 a funcao que deve ser executada
    ldr r1, [sp, #4]                    @Coloca em r1 o tempo de sistema na qual a funcao deve ser exexutada
    msr CPSR_c, #0x13                   @Ativa o modo SUPERVISOR

    @Configura os parametros para adicionar os alarmes
    ldr r3, =ALARMS_COUNTER             @Coloca em r3 a posicao da variavel que contem o numero de alarmes ja adicionados
    ldr r4, =ARRAY_POSITION_FUNCTIONS   @Coloca em r4 o inicio do vetor de funcoes
    ldr r5, =ARRAY_TIME_ALARMS          @Coloca em r5 o inicio do vetor de tempos dos alarmes
    mov r6, #4                          @Coloca em r6 o numero de bytes de uma instrucao

    @Trata erros
    ldr r8, [r3]                        @Coloca em r8 o valor do numero de alarmes adicionados
    cmp r8, #8                          @Compara com o numero de alarmes maximos
    beq RETURN_ERROR1                   @Salta para o tratador de erros

    @Verifica uma posicao disponivel para adicionar o alarme
    loop_add:
      ldr r2, [r4]                      @Coloca em r2 o valor existente na posicao do vetor de funcoes que esta em r4
      ldr r6, [r5]                      @Coloca em r6 o valor existente na posicao do vetor de tempos que esta em r5
      cmp r2, #0                        @Compara se o endereco da funcao que deve saltar eh zero
      beq add_alarms                    @Caso seja zero, a posicao esta disponivel e salta para armazenar no vetor
      add r4, r4, #4                    @Salta uma posicao no vetor de funcoes
      add r5, r5, #4                    @Salta uma posicao no vetor de tempos
      b loop_add                        @Salta para o inicio do loop

    @Adiciona os alarmes
    add_alarms:
    str r0, [r4]                        @Adiciona a funcao no vetor de funcoes
    str r1, [r5]                        @Adiciona o tempo de sistema na qual essa funcao deve ser executada
    ldr r1, [r5]

    @Atualiza o numero de alarmes
    ldr r3, =ALARMS_COUNTER             @Coloca em r3 a posicao da variavel que contem o numero de alarmes ja adicionados
    ldr r8, [r3]                        @Coloca em r8 o numero de alarmes ja adicionados
    add r8, r8, #1                      @Soma um para o novo alarme adicionado
    str r8, [r3]                        @Grava o novo numero de alarmes

    @Registradores para debugar
    @ldr r3, [r3]                        @Registrador para ver o numero de alarmes adicionados
    @ldr r8, [r4]                    @Registrador para saber se a funcao foi adicionada corretamente
    @ldr r9, [r5]                    @Registrador para saber se o tempo foi adicionado corretamente

    pop {r1-r12, lr}                    @Recupera todos os registradores salvos
    movs pc, lr                         @Retorna para o programa do usuario

REGISTER_PROXIMITY_CALLBACK:
    push {r1-r12, lr}   			      @Salva todos os registradores

    msr CPSR_c, #0x1F   		        @Ativa o modo system
    ldr r0, [sp]    			          @Recebe o id do sonar em r0
    ldr r1, [sp, #4]    		        @Recebe limiar de distancia
    ldr r2, [sp, #8]    		        @Recebe endereco da funcao para pular
    msr CPSR_c, #0x13   		        @Ativa o modo supervisor

    @Configura parametros para adicionar as callbacks
    ldr r3, =PROX_COUNTER   		    @Coloca em r3 a posicao da variavel que contem o numero de callbacks
    ldr r4, =ARRAY_ID_PROX          @Coloca em r4 o inicio do vetor dos IDS
    ldr r5, =ARRAY_DIST_PROX        @Coloca em r5 o inicio do vetor das limiares
    ldr r6, =ARRAY_POSITION_PROX    @Coloca em r6 o inicio do vetor das funcoes
    mov r7, #4                      @Coloca em r6 o n de bytes de uma instrucao

    @ Verifica erros
    ldr r3, [r3]                    @Registrador para ver o numero de callbacks adicionado
    cmp r3, #8                      @Compara com 8 para retornar erros
    beq RETURN_ERROR1               @Pula para retornar erros
    cmp r0, #15                     @Compara com 15 para verificar erro nos sonares
    bhi RETURN_ERROR2               @Pula para retornar erros

    @Adiciona as callbacks
    mul r8, r3, r7                  @Coloca em r8 a posicao na qual a callback e seus respectivos id e limiar devem ser adicionados
    str r0, [r4, r8]                @Adiciona o ID no vetor de ID's
    str r1, [r5, r8]                @Adiciona a limiar no vetor das LIMIARES
    str r2, [r6, r8]                @Adiciona a funcao no vetor das funcoes

    ldr r2, [r6, r8]

    @Atualiza o numero de callbacks
    ldr r3, =PROX_COUNTER           @Coloca em r3 a posicao do prox PROX_COUNTER
    ldr r9, [r3]                    @Coloca em r9 o numero de callbacks
    add r9, r9, #1                  @Soma 1 callback
    str r9, [r3]                    @Grava o novo numero

    @Registradores para debugar
    @ldr r3, [r3]
    @ldr r9, [r4, r8]
    @ldr r10, [r5, r8]
    @ldr r11, [r6, r8]

    mov r0, #0
    pop {r1-r12, lr}
    movs pc, lr

RETURN_ERROR1:
    mov r0, #-1
    pop {r1-r12, lr}
    movs pc, lr

RETURN_ERROR2:
    mov r0, #-2
    pop {r1-r12, lr}
    movs pc, lr

.data
  SYSTEM_TIME:
  .word 0

  ALARMS_COUNTER:
  .word 0

  PROX_COUNTER:
  .word 0

  COUNTER_DIST_INTERVAL:
  .word 0

  ARRAY_TIME_ALARMS:
  .skip 32

  ARRAY_POSITION_FUNCTIONS:
  .skip 32

  ARRAY_ID_PROX:
  .skip 32

  ARRAY_DIST_PROX:
  .skip 32

  ARRAY_POSITION_PROX:
  .skip 32
