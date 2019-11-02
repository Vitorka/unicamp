    .global set_motor_speed
    .global set_motors_speed
    .global read_sonar
    .global read_sonars
    .global register_proximity_callback
    .global add_alarm
    .global get_time
    .global set_time

    .align 4

set_motor_speed:

    push {r4-r11, lr}           @Push nos registradores r4-r11 e lr

    ldrb r4, [r0], #1           @Armazena em r4, o id do motor
    ldrb r5, [r0]               @Armazena em r5, o valor da velocidade do motor
    push {r4, r5}               @Empilha o id e o valor da velocidade, que serao passados
                                @como parametro para a syscall

    mov r7, #18                 @Realiza a chamada syscall (#18: set_motor_speed)
    svc 0x0

    pop {r4, r5}                @Desempilha os parametros empilhados
    pop {r4-r11, pc}            @Pop nos registradores r4-r11 e pc

set_motors_speed:

    push {r4-r11, lr}           @Push nos registradores r4-r11 e lr

    ldrb r4, [r0, #1]           @Armazena em r4 a velocidade do motor 0
    ldrb r5, [r1, #1]           @Armazena em r5 a velocidade do motor 1
    push {r4, r5}               @Empilha os valores de velocidade do motor 0 e motor 1,
                                @que serao passados como parametro para a syscall

    mov r7, #19                 @Realiza a chamada da syscall (#19: set_motors_speed)
    svc 0x0

    pop {r4, r5}                @Desempilha os parametros empilhados
    pop {r4-r11, pc}            @Pop nos registradores r4-r11 e pc

read_sonar:

    push {r4-r11, lr}           @Push nos registradores r4-r11 e lr

    push {r0}                   @Empilha o id do sonar que devera ser lido,
                                @que sera passado como parametro para a syscall

    mov r7, #16                 @Realizaa chamada da syscall (#16: read_sonar)
    svc 0x0

    pop {r1}                    @Desempilha o parametro empilhado
    pop {r4-r11, pc}            @Pop nos registradores r4-r11 e pc

read_sonars:

    push {r4-r11, lr}           @Push nos registradores r4-r11 e lr

    @Armazena os parametros da funcao
    mov r4, r0                  @Armazena em r4 o inicio do range de sonares que devem ser lidos
    mov r5, r1                  @Armazena em r5 o fim do range de sonares que devem ser lidos
    mov r3, #4
    mul r4, r4, r3              @Multiplica o inicio do range por 4 para ter a posicao do sonar lido
    add r6, r2, r4              @Armazena em r6 o inicio do vetor de distancias

    loop:                       @Loop para a leitura de todos os sonares desejados
        mov r0, r4              @Armazena em r0 o sonar que deve ser lido
        push {lr}               @Salva o lr
        bl read_sonar           @Chama a funcao read_sonar para ler o sonar desejado
        pop {lr}                @Recupera o lr
        str r0, [r6], #4        @Atualiza o vetor de distancias
        add r4, r4, #1          @Atualiza o sonar o proximo sonar que deve ser lido
        cmp r4, r5              @Verifica se todos os sonares ja foram lidos
        bls loop

    pop {r4-r11, pc}            @Pop nos registradores r4-r11 e pc

register_proximity_callback:

    push {r4-r11, lr}           @Push nos registradores r4-r11 e lr

    push {r0-r2}                @Empilha os parametros

    mov r7, #17                 @Realiza a chamada da syscall (#17: register_proximity_callback)
    svc 0x0

    pop {r0-r2}                 @Desempilha os parametros que foram empilhados
    pop {r4-r11, pc}            @Pop nos registradores r4-r11 e pc

add_alarm:

    push {r4-r11, lr}           @Push nos registradores r4-r11 e lr

    push {r0, r1}               @Empilha os parametros da funcao

    mov r7, #22                 @Realiza a chamada da syscall (#22: add_alarm)
    svc 0x0

    pop {r0, r1}

    pop {r4-r11, pc}            @Pop nos registradores r4-r11 e pc

get_time:

    push {r4-r11, lr}           @Push nos registradores r4-r11 e lr

    mov r4, r0                  @Armazena em r4 o endereco da variavel que ira receber o
                                @tempo do sistema

    mov r7, #20                 @Realiza a chamada da syscall (#20: get_time)
    svc 0x0

    str r0, [r4]                @Armazena o tempo do sistema na variavel

    pop {r4-r11, pc}            @Pop nos registradores r4-r11 e pc

set_time:

    push {r4-r11, lr}           @Push nos registradores r4-r11 e lr

    push {r0}                   @Empilha o novo tempo do sistema, que sera passado como parametro
                                @para a syscall

    mov r7, #21                 @Realiza a chamada da syscall (#21: set_time)
    svc 0x0

    pop {r1}                    @Desempilha o parametro que foi empilhado

    pop {r4-r11, pc}            @Pop nos registradores r4-r11 e pc
