CC = gcc
CFLAGS = -Wall -O2 -fopenmp -llapack -lopenblas
CFLAGSNOBLASO = -Wall -O2 -fopenmp -lblas
CLIBS = 

all:	hw1.c

gprof:
	$(CC) $(CFLAGS) -pg -o hw1 hw1.c $(CLIBS)

operf:
	$(CC) $(CFLAGS) -g -o hw1 hw1.c $(CLIBS)

perf:
	$(CC) $(CFLAGS) -ggdb -o hw1 hw1.c $(CLIBS)

blas:
	$(CC) hw1.c -o hw1 $(CFLAGSNOBLASO)

norm:
	$(CC) $(CFLAGS) -o hw1 hw1.c $(CLIBS)

clean:
	rm -rf hw1
