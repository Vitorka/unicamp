disk.img: ra178474 faznada
	mksd.sh --so ra178474 --user faznada

ra178474: ra178474.o
	arm-eabi-ld ra178474.o -g -o ra178474 --section-start=.iv=0x778005e0 -Ttext=0x77800700 -Tdata=0x77801800 -e 0x778005e0

ra178474.o: ra178474.s
	arm-eabi-as ra178474.s -g -o ra178474.o

faznada.o: faznada.s
	arm-eabi-as faznada.s -g -o faznada.o

faznada: faznada.o
	arm-eabi-ld faznada.o -g -o faznada -Tdata=0x77801800
