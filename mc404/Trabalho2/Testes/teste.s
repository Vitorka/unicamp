.global set_speed_motors
.global read_sonar
.global set_speed_motor
.align 4

set_speed_motors:

    @mov r0, #20   @Id do motor
    @mov r1, #20  @velocidade do motor
    push {r0, r1}
    mov r7, #19
    svc 0x0
    pop {r0, r1}

    mov pc, lr

read_sonar:

    push {r0}
    mov r7, #16
    svc 0x0
    pop {r2}

    mov pc, lr

set_speed_motor:

    push {r0, r1}
    mov r7, #18
    svc 0x0
    mov pc, lr

get_time:

    mov r0, #7
    svc 0x0
