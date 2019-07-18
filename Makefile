INC_PATH := -I/usr/local/include
CFLAGS = $(INC_PATH) -g -Wall -o2 -std=c++0x
CC=g++
SRC=$(wildcard *.cpp)
OBJ=$(addprefix ./, $(addsuffix .o, $(basename $(SRC))))
TARGET= MaJiang

all: $(TARGET)
 
$(TARGET): $(OBJ)
	$(CC) -O2 -g -Wall -o $(TARGET) $(OBJ)
	rm -f $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<
 
%.o: %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(TARGET) $(OBJ)

