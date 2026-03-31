CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g -I Headers

SOURCES_DIR = Sources
HEADERS_DIR = Headers
PQUEUE_DIR = pqueue
EXCEPTION_DIR = exception

PQUEUE_SRC = $(SOURCES_DIR)/$(PQUEUE_DIR)/priorityqueue.cpp
EXCEPTION_SRC = $(SOURCES_DIR)/$(PQUEUE_DIR)/exceptions.cpp

DEMO_SRC = $(SOURCES_DIR)/demo.cpp
TEST_SRC = $(SOURCES_DIR)/test.cpp
MAIN_SRC = $(SOURCES_DIR)/main.cpp

PQUEUE_OBJ = priorityqueue.o
EXCEPTION_OBJ = exceptions.o
DEMO_OBJ = demo.o
TEST_OBJ = test.o
MAIN_OBJ = main.o

DEMO_EXE = demo
TEST_EXE = test
MAIN_EXE = main

all: module demo test main


module: $(PQUEUE_OBJ) $(EXCEPTION_OBJ)

$(PQUEUE_OBJ): $(PQUEUE_SRC) $(HEADERS_DIR)/priorityqueue.h $(HEADERS_DIR)/exceptions.h
	$(CXX) $(CXXFLAGS) -c $(PQUEUE_SRC) -o $(PQUEUE_OBJ)
	@echo "Built module: $(PQUEUE_OBJ)"

$(EXCEPTION_OBJ): $(EXCEPTION_SRC) $(HEADERS_DIR)/exceptions.h
	$(CXX) $(CXXFLAGS) -c $(EXCEPTION_SRC) -o $(EXCEPTION_OBJ)
	@echo "Built module: $(EXCEPTION_OBJ)"


demo: $(DEMO_EXE)

$(DEMO_EXE): $(PQUEUE_OBJ) $(EXCEPTION_OBJ) $(DEMO_OBJ)
	$(CXX) $(CXXFLAGS) $(PQUEUE_OBJ) $(EXCEPTION_OBJ) $(DEMO_OBJ) -o $(DEMO_EXE)
	@echo "Built demo: $(DEMO_EXE)"

$(DEMO_OBJ): $(DEMO_SRC) $(HEADERS_DIR)/all.h
	$(CXX) $(CXXFLAGS) -c $(DEMO_SRC) -o $(DEMO_OBJ)


run-demo: demo
	@echo "Running PriorityQueue Demo"
	./$(DEMO_EXE)


test: $(TEST_EXE)

$(TEST_EXE): $(PQUEUE_OBJ) $(EXCEPTION_OBJ) $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) $(PQUEUE_OBJ) $(EXCEPTION_OBJ) $(TEST_OBJ) -o $(TEST_EXE)
	@echo "Built test: $(TEST_EXE)"

$(TEST_OBJ): $(TEST_SRC) $(HEADERS_DIR)/all.h
	$(CXX) $(CXXFLAGS) -c $(TEST_SRC) -o $(TEST_OBJ)


run-test: test
	@echo "Running PriorityQueue Tests"
	./$(TEST_EXE)
	@echo "================================================"
	@echo "Test results written to log.txt"


main: $(MAIN_EXE)

$(MAIN_EXE): $(PQUEUE_OBJ) $(EXCEPTION_OBJ) $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) $(PQUEUE_OBJ) $(EXCEPTION_OBJ) $(MAIN_OBJ) -o $(MAIN_EXE)
	@echo "Built main: $(MAIN_EXE)"

$(MAIN_OBJ): $(MAIN_SRC) $(HEADERS_DIR)/all.h
	$(CXX) $(CXXFLAGS) -c $(MAIN_SRC) -o $(MAIN_OBJ)


run-main: main
	@echo "Running PriorityQueue Menu"
	./$(MAIN_EXE)


clean:
	rm -f $(PQUEUE_OBJ) $(EXCEPTION_OBJ) $(DEMO_OBJ) $(TEST_OBJ) $(MAIN_OBJ) $(DEMO_EXE) $(TEST_EXE) $(MAIN_EXE) log.txt
	@echo "Cleaned all build artifacts"


rebuild: clean all
	@echo "Rebuild complete"


.PHONY: all module demo run-demo test run-test main run-main clean rebuild

