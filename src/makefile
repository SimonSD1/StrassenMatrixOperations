GCC_FLAGS=-Wall -g 
EXEC= main

all: $(EXEC)

clean:
	rm -f *.o $(EXEC) *~

.c.o:   
	gcc $(GCC_FLAGS) -c $*.c

main: main.o proj.o
	gcc ${GCC_FLAGS} -o $@ $^

