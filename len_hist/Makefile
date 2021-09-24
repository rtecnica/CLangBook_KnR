CC = gcc
INCLUDES =
LIBS =
DEPS =
TARGET = len_hist
CFLAGS = -std=c11 -Wall -ggdb3
BUILD_FLAGS = -std=c11 -w -ggdb3

all: $(TARGET)

$(TARGET): $(TARGET).c
	$(CC) $(INCLUDES) -o $(TARGET) $(CFLAGS) $(TARGET).c $(DEPS) $(LIBS)

build: $(TARGET).c
	$(CC) $(INCLUDES) -o $(TARGET) $(BUILD_FLAGS) $(TARGET).c $(DEPS) $(LIBS)

try: $(TARGET)
	./$(TARGET)

clean: 
	rm $(TARGET)
