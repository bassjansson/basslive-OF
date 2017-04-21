
CC      = c++
CFLAGS  = -Wall
LDFLAGS =

OBJECTS = fft.o FourierTransform.o

all: FFT_Test

FFT_Test: $(OBJECTS)
	$(CC) -o $@ $(CFLAGS) $(OBJECTS) $(LDFLAGS)

.cpp.o:
	$(CC) -c $< $(CFLAGS)

clean:
	rm ./*.o
	rm ./FFT_Test

touch:
	touch ./*.cpp
	touch ./*.h
