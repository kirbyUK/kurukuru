CC=g++
FLAGS=-Wall -c -g
LIBS=-lsfml-graphics -lsfml-window -lsfml-system
SDIR=./
DESTDIR=/usr/local/bin/

kurukuru: main.o helirin.o interface.o theme.o level.o
	$(CC) $(LIBS) -g main.o helirin.o interface.o theme.o level.o \
					 -o kurukuru

main.o: $(SDIR)main.cpp
	$(CC) $(FLAGS) $(SDIR)main.cpp 

helirin.o: $(SDIR)helirin.h $(SDIR)helirin.cpp $(SDIR)constants.h
	$(CC) $(FLAGS) $(SDIR)helirin.cpp

interface.o: $(SDIR)interface.h $(SDIR)interface.cpp
	$(CC) $(FLAGS) $(SDIR)interface.cpp

theme.o: $(SDIR)theme.h $(SDIR)theme.cpp
	$(CC) $(FLAGS) $(SDIR)theme.cpp

level.o: $(SDIR)level.h $(SDIR)level.cpp
	$(CC) $(FLAGS) $(SDIR)level.cpp

.PHONY: install clean
install:
	cp kurukuru $(DESTDIR)

clean:
	rm *.o
