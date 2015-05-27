# Find all source files under ./src/
BEECHAT_CPP_FILES := $(wildcard src/*.cpp)

# Name object files after source files with ./obj/ prefixed to the filename
BEECHAT_OBJ_FILES := $(addprefix ./obj/,$(notdir $(BEECHAT_CPP_FILES:.cpp=.o)))

beechat: $(BEECHAT_OBJ_FILES)
	g++ -ansi -o BeeChat $(BEECHAT_OBJ_FILES) -lncurses -pthread

TEST_CPP_FILES :=  $(wildcard test/*.cpp)

TEST_OBJ_FILES := $(addprefix ./test/obj/,$(notdir $(TEST_CPP_FILES:.cpp=.o)))

tests: ./src/settings.cpp ./include/settings.h
	g++ -ansi -o testBeeChat -I ./include/  $(TEST_CPP_FILES) ./src/settings.cpp

# Links all object files to create executable
all: beechat tests

# Compile a source file into respective object file
# The all target will try to link each of the object files (obj/shape.o, obj/circle.o, etc...)
# This will match this target, and the appropriate source file will be entered as part of the dependency list, which is then used as the source file for g++
# -o $@ - use target as output file
# $< - dependencies, used as input to g++
obj/%.o: src/%.cpp
	g++ -ansi -I ./include/ -c -o $@ $<

clean:
	rm -fv ./obj/*.o
	rm -fv BeeChat
	rm -fv testBeeChat


