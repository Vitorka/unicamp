disk.img: p2
		mksd.sh --so /home/vaoki/simulador/dummyos.elf --user p2

p2: p2.o
		arm-eabi-ld p2.o -g -o p2 -Ttext=0x77802000 -Tdata=0x77802100

p2.o: p2.s
		arm-eabi-as p2.s -g -o p2.o

clean:
		rm -f p2.o p2 disk.img
