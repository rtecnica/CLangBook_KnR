SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = bin
CC = gcc
INCLUDES = $(wildcard $(INCLUDE_DIR)/*.h)
LIBS =
DEPS = $(wildcard $(SRC_DIR)/*.c)
TARGET = cross_ref
CFLAGS = -std=c11 -Wall -ggdb3 -O3
CPPFLAGS = -I$(INCLUDE_DIR) -MMD -MP
BUILD_FLAGS = -std=c11 -w -ggdb3 

.PHONY: all
all: makedirs $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(TARGET).c $(DEPS) 
	$(CC) $(CPPFLAGS) $(INCLUDES) -o $(BUILD_DIR)/$(TARGET) $(CFLAGS) $(TARGET).c $(DEPS) $(LIBS)

.PHONY: makedirs
makedirs: $(BUILD_DIR)/

$(BUILD_DIR)/:
	mkdir $(BUILD_DIR)

build: $(TARGET).c
	$(CC) $(INCLUDES) -o $(BUILD_DIR)/$(TARGET) $(BUILD_FLAGS) $(TARGET).c $(DEPS) $(LIBS)

try: $(BUILD_DIR)/$(TARGET)
	./$(BUILD_DIR)/$(TARGET)

clean: 
	rm $(BUILD_DIR)/$(TARGET)

clean-all:
	rm -r $(BUILD_DIR)
