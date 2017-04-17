
CC      = c++
CFLAGS  = -Wall
LDFLAGS =

OBJECTS = Main.o Filter.o Complex.o

all: DFT_Test

DFT_Test: $(OBJECTS)
	$(CC) -o $@ $(CFLAGS) $(OBJECTS) $(LDFLAGS)

.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	rm ./*.o
	rm ./DFT_Test

touch:
	touch ./*.cpp
	touch ./*.h
