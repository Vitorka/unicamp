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

    @Set interrupt table base address on coprocessor 15.
    ldr r0, =interrupt_vector
    mcr p15, 0, r0, c12, c0, 0

SET_TIME_SZ:

    .set TIME_SZ, 100

@Posicao inicial de memoria do programa do usuario
SET_PROGRAM_USER_POSITION:

    .set PROGRAM_USER, 0x77802000

@Posicao inicial de memoria das stacks de usuario e supervisor
SET_STACK_POSITIONS:

    .set STACK_USER, 0x77803000
    .set STACK_SUPERVISOR, 0x77803200
    .set STACK_IRQ, 0x77803300

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

    @msr CPSR_c, #0x12
    push {r0-r2}

    @Liga o controlador de interrupcoes
    ldr r1, =GPT_BASE

    @Configura GPT_SR
    mov r0, #0x1
    str r0, [r1, #GPT_SR]
    sub lr, lr, #4
    ldr r2, =SYSTEM_TIME
    ldr r0, [r2]
    add r0, r0, #1
    str r0, [r2]

    pop {r0-r2}

    movs pc, lr

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
    @cmp r7, #17
    @beq REGISTER_PROXIMITY_CALLBACK
    cmp r7, #18
    beq SET_MOTOR_SPEED
    cmp r7, #19
    beq SET_MOTORS_SPEED
    cmp r7, #20
    beq GET_TIME
    cmp r7, #21
    beq SET_TIME
    @cmp r7, #22
    @beq SET_ALARM


SET_MOTOR_SPEED:

    push {r0-r12}           @Salva todos os registradores
    msr CPSR_c, #0x1F       @Ativa o modo SYSTEM

    ldr r0, [sp]            @Recupera o parametro 1: id_motor
    ldr r1, [sp, #4]        @Recupera o parametro 2: speed_motor

    msr CPSR_c, #0x12       @Ativa o modo SUPERVISOR
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

    pop {r0-r12}

    movs pc, lr

SET_MOTOR_0:

    mov r1, r1, lsl #19     @Desloca os bits ate a posica que indica a
                            @velocidade do motor 0

    ldr r4, =0b11111110000000111111111111111111   @Mascara de bits para zerar
                                                  @a velocidade antiga em DR
    ldr r5, [r3, #GPIO_DR]  @Recupera o valor do registrador DR

    ldr r6, [r3, #GPIO_GDIR]

    and r5, r5, r4          @Aplica um AND para zerar o valor antigo da
                            @velocidade do motor em DR
    orr r5, r5, r1          @Aplica um OR para setar a nova velocidade do motor

    str r5, [r3, #GPIO_DR]  @Salva em DR a velocidade do motor

    pop {r0-r12}

    movs pc, lr

SET_MOTORS_SPEED:

    push {r0-r12}	@Salva todos os registradores, no modo SUPERVISOR
    msr CPSR_c, #0x1F	@Ativa o modo SYSTEM

    ldr r0, [sp]            @Recupera o parametro 1: speed_motor 0
    ldr r1, [sp, #4]        @Recupera o parametro 2: speed_motor 1

    msr CPSR_c, #0x13       @Ativa o modo SUPERVISOR
    ldr r3, =GPIO_BASE	@Pega a posicao inicial do GPIO

    mov r0, r0, lsl #19	@Desloca os bits ate a posicao que indica a velocidade do motor 0
    mov r1, r1, lsl #26	@Desloca os bits ate a posicao que indica a velocidade do motor 1

    ldr r4, =0b00000000000000111111111111111111 @Mascara de bits para zerar a velocidade antiga em DR

    ldr r5, [r3, #GPIO_DR]	@Recupera valor em DR

    and r5, r5, r4		@Aplica um AND para zerar os valores anitogs das velocidades em DR

    orr r5, r5, r0		@Aplica um OR para setar a velocidade do motor 0
    orr r5, r5, r1		@Aplica um OR para setar a velocidade do motor 1

    orr r5, r5, r4      @Aplica a mascara a velocidade

    str r5, [r3, #GPIO_DR] 	@Salva em DR a velocidade do motor

    pop {r0-r12}		@Esvazia pilha do modo supervisor

    movs pc, lr			@Volta para o text

READ_SONAR:

    push {r1-r12}  @Salva todos os registradores

    @Recupera os parametros
    msr CPSR_c, #0x1F       @Muda para o modo SYSTEM
    ldr r0, [sp]            @Recupera o parametro 1: id_sonar
    mov r0, r0, lsl #2      @Desloca o valor de id_sonar para a posicao SONAR_MUX em DR

    msr CPSR_c, #0x13
    @Recupera e modifica DR
    ldr r1, =GPIO_BASE      @Coloca em r1 o endereco base de GPIO
    ldr r2, [r1, #GPIO_DR]  @Coloca em r2, DR
    ldr r3, =0b11111111111111111111111111000001 @Mascara para zerar o que existia em SONAR_MUX e TRIGGER em DR
    and r2, r2, r3          @Zera o campo SONAR_MUX em DR
    orr r2, r2, r0          @Adiciona em r2 o id do sonar a ser lido
    str r2, [r1, #GPIO_DR]  @Adiciona em DR o id do sonar a ser lido

    @Delay
    ldr r4, =SYSTEM_TIME
    ldr r4, [r4]            @Recupera a variavel que contem o valor do tempo de sistema
    add r4, r4, #15         @Adiciona a ela o tempo de delay
    @Aguarda ter passado o tempo de delay necessario no tempo do sistema
    delay_1:
      ldr r5, =SYSTEM_TIME
      ldr r5, [r5]
      cmp r4, r5
      bne delay_1

    rot1:
    @Modifica o TRIGGER para 1
    ldr r2, [r1, #GPIO_DR]  @Coloca em r2, DR
    ldr r3, =0b00000000000000000000000000000010 @Mascara para setar o TRIGGER como 1
    orr r2, r2, r3          @Seta em r2 o TRIGGER como 1
    str r2, [r1, #GPIO_DR]  @Seta em DR o TRIGGER como 1

    @Delay
    ldr r4, =SYSTEM_TIME
    ldr r4, [r4]            @Recupera a variavel que contem o valor do tempo de sistema
    add r4, r4, #15         @Adiciona a ela o tempo de delay
    @Aguarda ter passado o tempo de delay necessario no tempo do sistema
    delay_2:
      ldr r5, =SYSTEM_TIME
      ldr r5, [r5]
      cmp r4, r5
      bne delay_2

    rot2:
    @Modifica o TRIGGER para 0
    ldr r2, [r1, #GPIO_DR]  @Coloca em r2, DR
    ldr r3, =0b11111111111111111111111111111101 @Mascara para setar o TRIGGER como 0-
    and r2, r2, r3          @Seta em r2 o TRIGGER como 0
    str r2, [r1, #GPIO_DR]  @Seta em DR o TRIGGER como 0

    verifica_flag:

      @Delay
      ldr r4, =SYSTEM_TIME
      ldr r4, [r4]            @Recupera a variavel que contem o valor do tempo de sistema
      add r4, r4, #15         @Adiciona a ela o tempo de delay
      @Aguarda ter passado o tempo de delay necessario no tempo do sistema
      delay_3:
        ldr r5, =SYSTEM_TIME
        ldr r5, [r5]
        cmp r4, r5
        bne delay_3

      rot3:
      ldr r2, [r1, #GPIO_DR] @Coloca em r2, DR
      ldr r3, =0b00000000000000000000000000000001 @Mascara para recuperar somente o bit da FLAG
      and r2, r2, r3         @Aplica em r2 a mascara para recuperar o bit da FLAG
      cmp r2, #1             @Confere se a FLAG tem valor 1
      bne verifica_flag      @Caso nao tenha, faz a verificacao novamente

    rot4:
    ldr r2, [r1, #GPIO_DR] @Coloca em r2, DR
    mov r0, r2, lsr #6      @Retorna em r0 o valor da distancia lida
    ldr r3, =0b00000000000000000000111111111111 @Mascara para pegar somente o vaor da distancia lida
    and r0, r0, r3

    pop {r1-r12}

    movs pc, lr

SET_TIME:
    push {r1-r12}	@Salva todos os registradores
    msr CPSR_c, #0x1F	@Muda para modo system
    ldr r0, [sp]	@Carrega em r0 o parametro que é o time a ser setado
    msr CPSR_c, #0x13	@Ativa modo supervisor
    ldr r1, =SYSTEM_TIME	@Carrega endereço de System_time em r1
    str r0, [r1]	@Da store do novo tempo na posicao do system_time
    pop {r1-r12}

    movs pc, lr

GET_TIME:
    push {r1-r12}	@Salva todos os registradores
    MSR CPSR_c, #0x1F	@ativa modo system
    ldr r1, [sp]	@carrega em r1 o parametro que é a posicao a receber o tempo
    ldr r0, =SYSTEM_TIME@carrega em r0 a posicao do system_time
    ldr r0, [r0]	@Carrega novamente no proprio r0 o valor do system_time
    str r0, [r1]	@Coloca na posicao r1 o tempo atual
    pop {r1-r12}

    movs pc, lr

.data
  SYSTEM_TIME:
