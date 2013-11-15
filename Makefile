#Makefile for FRAME

SRC_FILES = ${shell find . -name "*.cpp"}
EXECUTABLE = FRAME
BUILD_DIR = Build

OBJ_FILES = $(subst ./,./$(BUILD_DIR)/,$(SRC_FILES:.cpp=.o))

DEPENDANCIES =  $(OBJ_FILES:.o=.d)

DIRECTORIES = $(patsubst .%,./$(BUILD_DIR)%,$(shell find . -not -iwholename "./$(BUILD_DIR)*" -not -iwholename "./.*" -type d))

GENERATED = ./Graphics/GLFunctions.h

CC = g++
CFLAGS = -std=c++11 -Wall -Wextra -fno-exceptions -fno-rtti -g -D DEBUG=1 -D COLOUR_TERMINAL=1

LD = g++
LDFLAGS = -lGL -lSDL2 -lSDL2_ttf -lSDL2_image -lassimp

ifdef DEPENDANCIES_GENERATED
include $(DEPENDANCIES)
endif

#Generate Dependancies
all: $(DIRECTORIES) $(GENERATED) $(DEPENDANCIES)
	@echo "-------------------------------"
	@echo "Compiling : "
	@echo "-------------------------------"
	@$(MAKE) DEPENDANCIES_GENERATED=1 CFLAGS='$(CFLAGS)' BUILD_DIR='$(BUILD_DIR)' $(EXECUTABLE)

#Generated Files
./Graphics/GLFunctions.h: GLFunctions.list GenerateGLFunction.py
	@echo "Generating GLFunctions.{h,cpp}"
	@python GenerateGLFunction.py

#Create Directories
$(DIRECTORIES):
	@echo "Creating Directory : $@"
	@test -d $@ || mkdir -p $@

#Generate Dependancies
./$(BUILD_DIR)/%.d : %.cpp
	@echo "Generating Dependancy file for $*.cpp"
	@$(CC) -MM $(CDEPFLAGS) -MT ./$(BUILD_DIR)/$*.o $*.cpp > ./$(BUILD_DIR)/$*.d

#Objects : Source
./$(BUILD_DIR)/%.o : %.cpp
	$(CC) -c $(CFLAGS) $*.cpp -o ./$(BUILD_DIR)/$*.o

#Clean
clean:
	rm -f -r $(BUILD_DIR)
	rm -f ./Graphics/GLFunctions.{h,cpp}

#Executable : Objects
$(EXECUTABLE) : $(OBJ_FILES)
	$(LD) -o $(EXECUTABLE) $(OBJ_FILES) $(LDFLAGS)
