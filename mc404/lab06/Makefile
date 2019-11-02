disk.img: ra178474 
	mksd.sh --so /home/vaoki/simulador/dummyos.elf --user ra178474
	
ra178474: ra178474.o
	arm-eabi-ld ra178474.o -o ra178474 -Ttext=0x77802000 -Tdata=0x77802400

ra178474.o: ra178474.s
	arm-eabi-as ra178474.s -o ra178474.o

