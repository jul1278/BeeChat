# Find all source files under ./src/
CPP_FILES := $(wildcard src/*.cpp)

# Name object files after source files with ./obj/ prefixed to the filename
OBJ_FILES := $(addprefix ./obj/,$(notdir $(CPP_FILES:.cpp=.o)))

# Links all object files to create executable
all: $(OBJ_FILES)
	g++ -ansi -o BeeChat $(OBJ_FILES) -lncurses -pthread

# Compile a source file into respective object file
# The all target will try to link each of the object files (obj/shape.o, obj/circle.o, etc...)
# This will match this target, and the appropriate source file will be entered as part of the dependency list, which is then used as the source file for g++
# -o $@ - use target as output file
# $< - dependencies, used as input to g++
obj/%.o: src/%.cpp
	g++ -ansi -I ./include/ -c -o $@ $<

clean:
	rm ./obj/*.o
	rm BeeChat







# # Find all source files under ./src/
# # CPP_FILES := $(wildcard src/*.cpp)
# CPP_FILES := $(wildcard */*.cpp)

# # subdirs := $(wildcard */)
# # sources := $(wildcard $(addsuffix *.cpp,$(subdirs)))
# # objects := $(patsubst %.cpp,%.o,$(sources))

# # $(objects) : %.o : %.cpp

# # Name object files after source files with ./obj/ prefixed to the filename
# OBJ_FILES := $(addprefix ./obj/,$(notdir $(CPP_FILES:.cpp=.o)))

# # Links all object files to create executable
# all: $(OBJ_FILES)
# 	g++ -ansi -o test $(OBJ_FILES) -lncurses -pthread

# # Compile a source file into respective object file
# # The all target will try to link each of the object files (obj/shape.o, obj/circle.o, etc...)
# # This will match this target, and the appropriate source file will be entered as part of the dependency list, which is then used as the source file for g++
# # -o $@ - use target as output file
# # $< - dependencies, used as input to g++
# obj/%.o: src/%.cpp
# 	g++ -ansi -I ./include/ -c -o $@ $<

# clean:
# 	rm ./obj/*.o
# 	rm test

