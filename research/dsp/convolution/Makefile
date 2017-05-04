
CC      = c++
CFLAGS  = -Wall
LDFLAGS =

OBJECTS = Main.o FourierTransform.o

all: Convolution

Convolution: $(OBJECTS)
	$(CC) -o $@ $(CFLAGS) $(OBJECTS) $(LDFLAGS)

.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	rm ./*.o
	rm ./Convolution

touch:
	touch ./*.cpp
	touch ./*.h
