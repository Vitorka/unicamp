.text
_start:

  mov r7, #20
  svc 0x0
  mov r0, r0

@  mov r0, #36   @Id do motor
@  mov r1, #36  @velocidade do motor
@  push {r0, r1}
@  mov r7, #19
@  svc 0x0
@  pop {r0, r1}

@  loop:

@    mov r0, #3
@    push {r0}
@    mov r7, #16
@    svc 0x0
@    cmp r0, #1200
@  bhs loop

@  mov r0, #0   @Id do motor
@  mov r1, #0  @velocidade do motor
@  push {r0, r1}
@  mov r7, #19
@  svc 0x0
@  pop {r0, r1}

@  mov pc, lr
