# For Linux or any machines with gcc compiler
CC = gcc
CFLAGS = -std=c99 -ansi -Wall -pedantic 

# For SunOS
#CFLAGS = -Aa

all: Example fir_lpf fir_sharpening iir

clean:
	/bin/rm *.o Example fir_lpf fir_sharpening iir

OBJ = tiff.o allocate.o randlib.o utils.o

Example: Example.o $(OBJ) 
	$(CC) $(CFLAGS) -o Example Example.o $(OBJ) -lm

fir_lpf: fir_lpf.o $(OBJ) 
	$(CC) $(CFLAGS) -o fir_lpf fir_lpf.o $(OBJ) -lm

fir_sharpening: fir_sharpening.o $(OBJ) 
	$(CC) $(CFLAGS) -o fir_sharpening fir_sharpening.o $(OBJ) -lm

iir: iir.o $(OBJ) 
	$(CC) $(CFLAGS) -o iir iir.o $(OBJ) -lm
