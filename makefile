OUTPUT :=obrazy2.out

#*.h dir
IDIR :=include
#*.o dir
ODIR :=obj
#*.h lib dir
LDIR :=lib
#*.c dir
SDIR :=src

CC :=gcc
CFLAGS :=-I$(IDIR) -Wall -pedantic -std=c99
LIBS :=-lm

#*.h
_DEPS := o2_dane.h o2_edycja.h o2_io.h o2_main.h o2_pamiec.h opcje.h
DEPS := $(patsubst %,$(IDIR)/%,$(_DEPS))

#*.o
_OBJ := o2_edycja.o o2_io.o o2_main.o o2_pamiec.o opcje.o
OBJ := $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OUTPUT): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o
