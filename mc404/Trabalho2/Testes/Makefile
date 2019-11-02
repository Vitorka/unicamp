disk.img: SO teste
	mksd.sh --so SO --user teste

SO: SO.o
	arm-eabi-ld SO.o -g -o SO --section-start=.iv=0x778005e0 -Ttext=0x77800700 -Tdata=0x77801800 -e 0x778005e0

SO.o: SO.s
	arm-eabi-as SO.s -g -o SO.o

teste.o: teste.s
	arm-eabi-as teste.s -g -o teste.o

teste: teste.o main.o
	arm-eabi-ld main.o teste.o -g -o teste -Ttext=0x77802000 -Tdata=0x77802100

#teste: teste.o
#	arm-eabi-ld teste.o -g -o teste -Ttext=0x77802000 -Tdata=0x77802100

main.o: main.s
		arm-eabi-as main.s -g -o main.o

main.s: main.c
	arm-eabi-gcc main.c -S -g -o main.s

clean:
	rm -f main.s main.o teste.o teste SO.o SO disk.img
