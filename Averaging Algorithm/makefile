IDIR=include
SDIR=src
ODIR=build

CC=mpicc
CFLAGS=-I $(IDIR)

# Edit sources here..
_SRCS = avg_time_algo.c
SRCS = $(patsubst %,$(SDIR)/%,$(_SRCS))

mpiAvgTimeAlgo: $(SRCS)
	@echo "\nAttempting to build\n"
	$(CC) -o $(ODIR)/$@ $^ $(CFLAGS)
	@echo "\nDone. Binary can be found in build/\n"

.PHONY: clean

clean:
	rm $(ODIR)/*.o