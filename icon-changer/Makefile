#######################################################################################################
# Module history:                                                                                     #
#   Date:       Author:                    Reason:                                                    #
#   27.06.2023  Gaina Stefan               Initial version.                                           #
#   05.08.2023  Gaina Stefan               Removed unnecessary comment.                               #
#   14.08.2023  Gaina Stefan               Added include flag.                                        #
# Description: This Makefile is used to generate the tool's executable.                               #
#######################################################################################################

CFLAGS = -Wall -Werror 

INCLUDES = -Iinclude/

SOURCES    := $(wildcard $(SRC)/*.c)
OBJECTS    := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))
EXECUTABLE := icon-changer.exe

all: | create_dirs $(EXECUTABLE)

### CREATE DIRECTORIES ###
create_dirs:
	if not exist "$(OBJ)" mkdir $(OBJ)
	if not exist "$(BIN)" mkdir $(BIN)

### BINARIES ###
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(BIN)/$@ $^

### OBJECTS ###
$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

### CLEAN ###
clean:
	del /f /q $(OBJ)\*
	del /f /q $(BIN)\*
