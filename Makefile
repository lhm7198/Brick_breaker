TARGET	=	3-codiots 
OBJECT	= 	main.o GameRunner.o
CC	=	g++

# directory
INCLUDE_DIR	=	/home/lhm7198/SFML/SFML-2.5.1/include/
LIBS		=	-lsfml-graphics -lsfml-window -lsfml-system

$(TARGET) 	:	$(OBJECT)
	$(CC) -o $@ $^ $(LIBS)

main.o 		:	main.cpp
	$(CC) -c $< -I INCLUDE_DIR

GameRunner.o	:	GameRunner.cpp
	$(CC) -c $< -I INCLUDE_DIR

clean	:
	rm -f *.o 3-codiots
