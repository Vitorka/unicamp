disk.img: robot_ctrl
	mksd.sh --so /home/vaoki/simulador/simulador_player/bin/knrl --user robot_ctrl

robot_ctrl: main.o api_robot.o
	arm-eabi-ld main.o api_robot.o -g -o robot_ctrl -Ttext=0x77802000

api_robot.o: api_robot.s
	arm-eabi-as api_robot.s -g -o api_robot.o

main.o: main.s
	arm-eabi-as main.s -g -o main.o

main.s: main.c
	arm-eabi-gcc main.c -g -S -o main.s
