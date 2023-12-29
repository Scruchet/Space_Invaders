CC=gcc
TARGET=main
LDFLAGS= -lgraph -lSDL -lSDL_ttf -LGraphique
# Makefile for project S6 space invaders
CFLAGS=-g -W -Wall -Wextra
 
default: $(TARGET)


liste.o: Liste/liste.c Liste/liste.h
	cd Graphique/ && make && cd .. && $(CC) $(CFLAGS) -c Liste/liste.c

main.o: main.c Liste/liste.h
	$(CC) $(CFLAGS) -c main.c

$(TARGET): main.o liste.o
	$(CC) main.o liste.o -o $(TARGET) $(LDFLAGS)
.PHONY: clean
clean:
	rm -f *.o
	rm -f $(TARGET)

format:
	clang-format -i -style="WebKit" main.c Liste/liste.c Liste/liste.h
tidy:
	clang-tidy main.c Liste/liste.c Liste/liste.h --checks="readability-*"
