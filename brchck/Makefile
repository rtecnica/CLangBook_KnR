CC = gcc
INCLUDES = br_stack.h
LIBS =
DEPS = br_stack.c
TARGET = brchck
CFLAGS = -std=c11 -Wall -ggdb3 -O3
BUILD_FLAGS = -std=c11 -w -ggdb3 -O3
BUILD_DIR = bin

all: $(TARGET)

$(TARGET): $(BUILD_DIR) $(TARGET).c
	$(CC) $(INCLUDES) -o ./$(BUILD_DIR)/$(TARGET) $(CFLAGS) $(TARGET).c $(DEPS) $(LIBS)

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

build: $(TARGET).c
	$(CC) $(INCLUDES) -o ./$(BUILD_DIR)/$(TARGET) $(BUILD_FLAGS) $(TARGET).c $(DEPS) $(LIBS)

try: $(TARGET)
	./$(TARGET)

clean: 
	rm $(TARGET)

clean-all:
	rm -r $(BUILD_DIR)
