COMMON_OBJECTS  =



CPU             = msp430g2553

CFLAGS          = -mmcu=${CPU} -I./lcdLib -I./timerLib

LDSCRIPT_DIR = /opt/ti/msp430_gcc/include

LDFLAGS         = -mmcu=${CPU} -L$(LDSCRIPT_DIR) -T msp430g2553.ld



# Compiler

CC              = msp430-elf-gcc

AS              = msp430-elf-as



all: TicTacToe.elf



# Target executable

TicTacToe.elf: ${COMMON_OBJECTS} main.o switches.o grid.o game_logic.o buzzer.o calledFunction.o assemblyFunction.o lcdLib/font-11x16.o lcdLib/lcddraw.o lcdLib/lcdutils.o lcdLib/font-5x7.o timerLib/clocksTimer.o timerLib/sr.o

	${CC} ${LDFLAGS} -o $@ $^



load: TicTacToe.elf

	msp430loader.sh TicTacToe.elf



clean:

	rm -f *.o *.elf

	rm -f lcdLib/*.o

	rm -f timerLib/*.o



# Rules for each object file

main.o: main.c switches.h grid.h game_logic.h lcdLib/lcddraw.h lcdLib/lcdutils.h buzzer.h assemblyFunction.h

	${CC} ${CFLAGS} -c main.c -o main.o



switches.o: switches.c switches.h grid.h game_logic.h lcdLib/lcddraw.h lcdLib/lcdutils.h

	${CC} ${CFLAGS} -c switches.c -o switches.o



grid.o: grid.c grid.h lcdLib/lcddraw.h lcdLib/lcdutils.h game_logic.h

	${CC} ${CFLAGS} -c grid.c -o grid.o



game_logic.o: game_logic.c game_logic.h grid.h lcdLib/lcddraw.h lcdLib/lcdutils.h buzzer.h

	${CC} ${CFLAGS} -c game_logic.c -o game_logic.o



buzzer.o: buzzer.c buzzer.h

	${CC} ${CFLAGS} -c buzzer.c -o buzzer.o



calledFunction.o: calledFunction.c calledFunction.h lcdLib/lcddraw.h lcdLib/lcdutils.h

	${CC} ${CFLAGS} -c calledFunction.c -o calledFunction.o



assemblyFunction.o: assemblyFunction.s calledFunction.h

	${AS} -mmcu=${CPU} assemblyFunction.s -o assemblyFunction.o



lcdLib/font-11x16.o: lcdLib/font-11x16.c

	${CC} ${CFLAGS} -c lcdLib/font-11x16.c -o lcdLib/font-11x16.o



timerLib/clocksTimer.o: timerLib/clocksTimer.c timerLib/libTimer.h

	${CC} ${CFLAGS} -c timerLib/clocksTimer.c -o timerLib/clocksTimer.o



timerLib/sr.o: timerLib/sr.s

	${AS} -mmcu=${CPU} timerLib/sr.s -o timerLib/sr.o



lcdLib/lcddraw.o: lcdLib/lcddraw.c lcdLib/lcddraw.h lcdLib/lcdutils.h

	${CC} ${CFLAGS} -c lcdLib/lcddraw.c -o lcdLib/lcddraw.o



lcdLib/lcdutils.o: lcdLib/lcdutils.c lcdLib/lcdutils.h

	${CC} ${CFLAGS} -c lcdLib/lcdutils.c -o lcdLib/lcdutils.o



lcdLib/font-5x7.o: lcdLib/font-5x7.c

	${CC} ${CFLAGS} -c lcdLib/font-5x7.c -o lcdLib/font-5x7.o

