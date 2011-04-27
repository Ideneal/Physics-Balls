CC = g++
LIBRERIE = -lSDL -lSDL_image

ifeq ($(NAME), )
	NAME = game
endif

compile: $(NAME)

%.o: %.cpp
	$(CC) -c $< -o $@

$(NAME): ball.o system.o main.o
	@echo "inizio compilazione..."
	$(CC) -o $@ $^ $(LIBRERIE)

clear: ball.o system.o main.o
	rm $^