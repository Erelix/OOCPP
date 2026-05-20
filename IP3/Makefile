CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -g
INCLUDE = -IHeaders

SOURCES = Sources/Exercise.cpp Sources/Exercises/Cardio.cpp Sources/Exercises/Strength.cpp \
          Sources/Exercises/Stretch.cpp Sources/ComputeStrategy.cpp Sources/FitnessProgram.cpp \
          Sources/exceptions.cpp
OBJECTS = $(SOURCES:.cpp=.o)
MODULE_OBJ = module.o

.PHONY: all module demo run test run_test clean rebuild help

all: module demo test

module: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -c $(OBJECTS)
	ar rcs $(MODULE_OBJ) $(OBJECTS)
	@echo "Module built: $(MODULE_OBJ)"

demo: $(OBJECTS) demo.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o demo $(OBJECTS) demo.cpp
	@echo "Demo built successfully"

run: demo
	@echo "Running demo..."
	@./demo

test: $(OBJECTS) test.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o test_program $(OBJECTS) test.cpp
	@echo "Test program built successfully"

run_test: test
	@echo "Running tests..."
	@./test_program

Sources/%.o: Sources/%.cpp Headers/*.h
	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@

clean:
	@rm -f $(OBJECTS) $(MODULE_OBJ) demo test_program
	@echo "Cleaned up object files and executables"

rebuild: clean all
	@echo "Full rebuild complete"

help:
	@echo "Fitness Program Makefile"
	@echo "Available targets:"
	@echo "  make module      - Build module.o from source files"
	@echo "  make demo        - Build demo executable"
	@echo "  make run         - Build and run demo"
	@echo "  make test        - Build test executable"
	@echo "  make run_test    - Build and run tests"
	@echo "  make clean       - Remove built files"
	@echo "  make rebuild     - Clean and rebuild everything"
	@echo "  make all         - Build module, demo, test"
	@echo "  make help        - Show this help message"
