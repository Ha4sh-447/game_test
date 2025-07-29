CC = clang++
CFlags = -Wall -g -Isrc
LDFlags = -lraylib -lm -ldl -lpthread -lGL -lX11

SRCS = main.cpp src/player.cpp src/animation.cpp src/config.cpp
OBJS = $(SRCS:.cpp=.o)

MAIN_EXEC = gooner
TESTER_EXEC = gooner_testies
all: $(MAIN_EXEC)
$(MAIN_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $(MAIN_EXEC) $(LDFlags)

%.o: %.cpp
	$(CC) $(CFlags) -c $< -o $@

run: all
	./$(MAIN_EXEC)

clean:
	rm -f $(OBJS) $(MAIN_EXEC)

.PHONY: all run clean
