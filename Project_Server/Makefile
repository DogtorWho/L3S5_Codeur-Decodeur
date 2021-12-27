SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin

LIBRARIES := # libraries

TARGET := exec

EXE := $(BIN_DIR)/$(TARGET)
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CPPFLAGS := -Iinclude -MMD -MP
CFLAGS   := -Wall $(LIBRARIES)
LDFLAGS  := -Llib
LDLIBS   := -lm

.PHONY : all run clean

all : $(EXE)

$(EXE) : $(OBJ) | $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BIN_DIR) $(OBJ_DIR) :
	mkdir -p $@

run : all
	./$(EXE)

clean :
	@$(RM) -rv $(BIN_DIR) $(OBJ_DIR)

-include $(OBJ:.o=.d)
