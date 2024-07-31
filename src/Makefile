.SUFFIXES:
.PRECIOUS: %.o
.PHONY: all compile checkstyle test clean

CXX = clang++ -fsanitize=address -std=c++17 -Wall -Wextra -Wdeprecated
MAIN_BINARY = $(basename $(wildcard *Main.cpp))
TEST_BINARY = $(basename $(wildcard *Test.cpp))
LIBS = -lSDL2 -lGL -lSDL2_image -lSDL2_ttf
TESTLIBS = -lgtest -lgtest_main -lpthread -std=c++17
OBJECTS = $(addsuffix .o, $(basename $(filter-out %Main.cpp %Test.cpp, $(wildcard *.cpp))))

all: compile test checkstyle

game: compile

compile: $(MAIN_BINARY) $(TEST_BINARY)

checkstyle:
	clang-format --dry-run -Werror *.h *.cpp

test: 
	./BlockTest
	./GameTest

%.o: %.cpp *.h
	$(CXX) -c $<

%Main: %Main.o $(OBJECTS)
	$(CXX) -o $@ $^ $(LIBS)

%Test: %Test.o $(OBJECTS)
	$(CXX) -o $@ $^ $(LIBS) $(TESTLIBS)

clean:
	rm -f *Main
	rm -f *Test
	rm -f *.o

format:
	clang-format -i *.cpp *.h