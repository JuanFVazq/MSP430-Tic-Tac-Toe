COMMON_OBJECTS  =
CPU             = msp430g2553
CFLAGS          = -mmcu=${CPU} -I./lcdLib -I./timerLib
LDFLAGS         = -L/opt/ti/msp430_gcc/include

# Compiler
CC              = msp430-elf-gcc
AS              = msp430-elf-as

all: TicTacToe.elf

# Target executable
TicTacToe.elf: ${COMMON_OBJECTS} main.o switches.o grid.o game_logic.o lcdLib/lcddraw.o lcdLib/lcdutils.o lcdLib/font-5x7.o timerLib/clocksTimer.o timerLib/sr.o
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

load: TicTacToe.elf
	msp430loader.sh TicTacToe.elf

clean:
	rm -f *.o *.elf
	rm -f lcdLib/*.o
	rm -f timerLib/*.o

# Rules for each object file
main.o: main.c switches.h grid.h game_logic.h lcdLib/lcddraw.h lcdLib/lcdutils.h
	${CC} ${CFLAGS} -c main.c -o main.o

switches.o: switches.c switches.h grid.h game_logic.h lcdLib/lcddraw.h lcdLib/lcdutils.h
	${CC} ${CFLAGS} -c switches.c -o switches.o

grid.o: grid.c grid.h lcdLib/lcddraw.h lcdLib/lcdutils.h
	${CC} ${CFLAGS} -c grid.c -o grid.o

game_logic.o: game_logic.c game_logic.h grid.h lcdLib/lcddraw.h lcdLib/lcdutils.h
	${CC} ${CFLAGS} -c game_logic.c -o game_logic.o

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
