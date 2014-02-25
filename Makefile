CC=g++
FLAGS=-Wall -c -g
LIBS=-lsfml-graphics -lsfml-window -lsfml-system
SDIR=./
DESTDIR=/usr/local/bin/

kurukuru: main.o kuru.o
	$(CC) $(LIBS)  -g main.o kuru.o -o kurukuru

main.o: $(SDIR)main.cpp
	$(CC) $(FLAGS) $(SDIR)main.cpp 

kuru.o: $(SDIR)kuru.h $(SDIR)kuru.cpp $(SDIR)constants.h
	$(CC) $(FLAGS) $(SDIR)kuru.cpp

.PHONY: install clean
install:
	cp kurukuru $(DESTDIR)

clean:
	rm *.o
