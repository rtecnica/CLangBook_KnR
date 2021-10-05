CC = gcc
INCLUDES = 
LIBS =
DEPS = 
TARGET = let_hist
CFLAGS = -std=c11 -Wall -ggdb3 -O3
BUILD_FLAGS = -std=c11 -w -ggdb3 
BUILD_DIR = bin

.PHONY: all
all: makedirs $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/$(TARGET): $(TARGET).c 
	$(CC) $(INCLUDES) -o $(BUILD_DIR)/$(TARGET) $(CFLAGS) $(TARGET).c $(DEPS) $(LIBS)

.PHONY: makedirs
makedirs: $(BUILD_DIR)/

$(BUILD_DIR)/:
	mkdir $(BUILD_DIR)

build: $(TARGET).c
	$(CC) $(INCLUDES) -o $(BUILD_DIR)/$(TARGET) $(BUILD_FLAGS) $(TARGET).c $(DEPS) $(LIBS)

try: $(TARGET)
	./$(BUILD_DIR)/$(TARGET)

clean: 
	rm $(BUILD_DIR)/$(TARGET)

clean-all:
	rm -r $(BUILD_DIR)
