#Makefile for FRAME

SRC_FILES = ${shell find . -name "*.cpp"}
EXECUTABLE = FRAME
BUILD_DIR = Build

OBJ_FILES = $(subst ./,./$(BUILD_DIR)/,$(SRC_FILES:.cpp=.o))

DEPENDANCIES =  $(OBJ_FILES:.o=.d)

DIRECTORIES = $(patsubst .%,./$(BUILD_DIR)%,$(shell find . -not -iwholename "./Build*" -not -iwholename "./.*" -type d))

GENERATED = ./Graphics/GLFunctions.h

CC = g++
CFLAGS = -std=c++11 -g -Wall -O2

LD = g++
LDFLAGS = -lGL -lSDL2 -lSDL2_ttf -lSDL2_image

#Include Dependancies
ifdef DEPENDANCIES_GENERATED
include $(DEPENDANCIES)
endif

#Generate Dependancies
all: $(DIRECTORIES) $(GENERATED) $(DEPENDANCIES)
	@echo "-------------------------------"
	@echo "Compiling : "
	@echo "-------------------------------"
	@$(MAKE) DEPENDANCIES_GENERATED=1 $(EXECUTABLE)

#Generated Files
./Graphics/GLFunctions.h: GLFunctions.list
	@echo "Generating GLFunctions.{h,cpp}"
	@python GenerateGLFunction.py

#Create Directories
$(DIRECTORIES):
	@echo "Creating Directory : $@"
	@test -d $@ || mkdir $@

#Generate Dependancies
./Build/%.d : %.cpp
	@echo "Generating Dependancy file for $*.cpp"
	@$(CC) -MM $(CFLAGS) $*.cpp > ./Build/$*.d

#Objects : Source
./Build/%.o : %.cpp
	$(CC) -c $(CFLAGS) $*.cpp -o ./Build/$*.o

clean:
	rm -f -r $(BUILD_DIR)
	rm -f ./Graphics/GLFunctions.{h,cpp}

$(EXECUTABLE) : $(OBJ_FILES)
	$(LD) -o $(EXECUTABLE) $(OBJ_FILES) $(LDFLAGS)
