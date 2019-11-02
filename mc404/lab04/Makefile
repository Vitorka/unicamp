disk.img: modelo
	mksd.sh --so /home/vaoki/simulador/dummyos.elf --user modelo

modelo: modelo.o
	arm-eabi-ld modelo.o -g -o modelo -Ttext=0x77802000 -Tdata=0x77802050

modelo.o: modelo.s
	arm-eabi-as modelo.s -g -o modelo.o
