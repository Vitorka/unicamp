disk.img: so api
	mksd.sh --so so --user api

so: so.o
	arm-eabi-ld so.o -g -o so --section-start=.iv=0x778005e0 -Ttext=0x77800700 -Tdata=0x77801800 -e 0x778005e0

so.o: so.s
	arm-eabi-as so.s -g -o so.o

api_robot2.o: api_robot2.s
	arm-eabi-as api_robot2.s -g -o api_robot2.o

api: api_robot2.o main.o
	arm-eabi-ld main.o api_robot2.o -g -o api -Ttext=0x77802000

#teste: teste.o
#	arm-eabi-ld teste.o -g -o teste -Ttext=0x77802000 -Tdata=0x77802100

main.o: main.s
		arm-eabi-as main.s -g -o main.o

main.s: main.c
	arm-eabi-gcc main.c -S -g -o main.s

clean:
	rm -f main.s main.o api_robot2.o api so.o so disk.img
