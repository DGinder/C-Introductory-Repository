#Darrin Vonbergen Bloodaxeaxe Ginder Lab6 Makefile
CC=gcc -lm
#Compiler flags: -g generate object code, -Wall
# option provides warnings
CFLAGS=-g -Wall
# All object modules identified
OBJ=main.o radius_inside_circle.o radius_outside_circle.o semi_perimeter.o
# Define name of executable, Lab6
EXE=Lab6
all:$(EXE)
# Rules begin here
$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $(EXE)
main.o: lab6.h main.c
	$(CC) $(CFLAGS) -c main.c
radius_inside_circle.o: lab6.h radius_inside_circle.c
	$(CC) $(CFLAGS) -c radius_inside_circle.c
radius_outside_circle.o: lab6.h radius_outside_circle.c
	$(CC) $(CFLAGS) -c radius_outside_circle.c
semi_perimeter.o: lab6.h semi_perimeter.c
	$(CC) $(CFLAGS) -c semi_perimeter.c
