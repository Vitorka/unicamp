.global set_speed_motors
.global read_sonar
.global set_time
.global get_time
.global add_alarm
.global register_proximity_callback
.align 4

@.text
@_start:

set_speed_motors:

    @mov r8, #20   @Id do motor
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

get_time:
    push {r0}
    mov r7, #20
    svc 0x0
    pop {r2}

    mov pc, lr

set_time:
    push {r0}
    mov r7, #21
    svc 0x0
    pop {r2}

    mov pc, lr

add_alarm:
    push {r0, r1}
    mov r7, #22
    svc 0x0
    pop {r0, r1}

    mov pc, lr

register_proximity_callback:
  push {r0, r1, r2}
  mov r7, #17
  svc 0x0
  pop {r0, r1, r2}

  mov pc, lr
