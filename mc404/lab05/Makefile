disk.img: hamming
	mksd.sh --so /home/vaoki/simulador/dummyos.elf --user hamming
	
hamming: hamming.o
	arm-eabi-ld hamming.o -g -o hamming -Ttext=0x77802000 -Tdata=0x77802500 

hamming.o: ra178474.s
	arm-eabi-as ra178474.s -g -o hamming.o

