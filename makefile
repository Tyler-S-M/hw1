CC = g++
CFLAGS = -fopenmp -llapack -lopenblaso
CLIBS = 
#CLIBS = -lblas

all:	hw1.cpp

gprof:
	$(CC) $(CFLAGS) -pg -o hw1 hw1.c $(CLIBS)

operf:
	$(CC) $(CFLAGS) -g -o hw1 hw1.c $(CLIBS)

perf:
	$(CC) $(CFLAGS) -ggdb -o hw1 hw1.c $(CLIBS)

norm:
	$(CC) hw1.c $(CFLAGS) -o hw1 $(CLIBS)

clean:
	rm -rf hw1
