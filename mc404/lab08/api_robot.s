    .global set_speed_motor
    .global set_speed_motors
    .global read_sonar
    .global read_sonars

    .align 4

set_speed_motor:

    stmfd sp!, {r4-r11, lr}
    cmp r1, #1      @Verifica se o id do motor eh 1
    beq motor1      @Caso seja 1, salta para motor1, para alterar a
                    @velocidade do motor1

    mov r7, #126    @Caso seja 0, altera a velocidade do motor 0
    svc 0x0         @Chama a syscall
    
    ldmfd sp!, {r4-r11, pc}

    motor1:
    mov r7, #127    @Caso seja 1, altera a velocidade do motor 1
    svc 0x0         @Chama a syscall

    ldmfd sp!, {r4-r11, pc}

set_speed_motors:

    stmfd sp!, {r4-r11, lr}

    mov r7, #124   @Altera as velocidades para os dois motores
    svc 0x0        @Chama a syscall

    ldmfd sp!, {r4-r11, pc}

read_sonar:

    stmfd sp!, {r4-r11, lr}

    mov r7, #125   @Le o sonar identificado pelo id
    svc 0x0        @Chama a syscall

    ldmfd sp!, {r4-r11, pc}

read_sonars:

    stmfd sp!, {r4-r11, lr}
    
    mov r4, r0     @Armazena a posicao inicial do vetor de distancias
    mov r0, #0     @Coloca em r0 a sonar que deve ser lido

    loop:
        mov r5, r0        @r2 = r0 Armazena qual o sonar esta sendo lido
        bl read_sonar     @Le a distancia captada pelo sonar
        str r0, [r4], #4  @Armazena na memoria o que foi lido pelo sonar 
        add r0, r5, #1    @Seta o proximo sonar a ser lido
        cmp r0, #15       @Verifica se todos os sonares ja foram lidos
        bls loop

    ldmfd sp!, {r4-r11, pc}
