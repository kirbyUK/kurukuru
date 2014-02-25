CC=g++
FLAGS=-Wall -c -g
LIBS=-lsfml-graphics -lsfml-window -lsfml-system
SDIR=./
DESTDIR=/usr/local/bin/

helirinhelirin: main.o helirin.o
	$(CC) $(LIBS)  -g main.o helirin.o -o kurukuru

main.o: $(SDIR)main.cpp
	$(CC) $(FLAGS) $(SDIR)main.cpp 

helirin.o: $(SDIR)helirin.h $(SDIR)helirin.cpp $(SDIR)constants.h
	$(CC) $(FLAGS) $(SDIR)helirin.cpp

.PHONY: install clean
install:
	cp kurukuru $(DESTDIR)

clean:
	rm *.o
