CC := g++

CFLAGS = -Wall -g

TARGET = bin/k-means
SRC_DIRS = src

SRCS = $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.cpp))
OBJS = $(SRCS:.cpp=.o)

all: clean $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)

clean:
	rm -f $(OBJS)
	rm -f $(EXE)

