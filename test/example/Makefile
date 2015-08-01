CC = g++
PRJ_HOME = ..
INCLUDE_DIR = .
SRC_DIR = .
TEST_DIR = ..

OPTIONS = -pthread -g
CPP_FILE = ${SRC_DIR}/factorial.cpp
TEST_FILE = ${TEST_DIR}/example/factorial_unit_test.cpp

.SUFFIXES: .h .o .cc
EXE_NAME = unit_test

# all compilation
all: 
	echo "   1. compile source code"
	$(CC) $(OPTIONS) -isystem$(TEST_DIR) -I$(INCLUDE_DIR) -c $(CPP_FILE)
	echo "   2. compile test source code"
	$(CC) $(OPTIONS) -isystem$(TEST_DIR) -I$(INCLUDE_DIR) -c $(TEST_FILE)
	echo "   3. compile gtest-all code"
	$(CC) $(OPTIONS) -isystem$(TEST_DIR) -c $(TEST_DIR)/gtest/gtest-all.cc
	echo "   4. compile gtest main code"
	$(CC) $(OPTIONS) -isystem$(TEST_DIR) -c $(TEST_DIR)/gtest/gtest_main.cc
	echo "   5. make final executable file >>"
	$(CC) $(OPTIONS) *.o -o $(EXE_NAME)
	rm *.o

# using library makes 'make' faster.
use-lib:
	echo "1. compile source code"
	$(CC) $(OPTIONS) -isystem$(TEST_DIR) -I$(INCLUDE_DIR) -c $(CPP_FILE)
	echo "2. compile test source code"
	$(CC) $(OPTIONS) -isystem$(TEST_DIR) -I$(INCLUDE_DIR) -c $(TEST_FILE)
	echo "3. make final executable file >>"
	$(CC) $(OPTIONS) *.o gtest_main.a -o $(EXE_NAME)
	rm *.o

# make a static library
make-lib: 
	echo "   1. compile gtest-all code"
	$(CC) $(OPTIONS) -isystem$(TEST_DIR) -c $(TEST_DIR)/gtest/gtest-all.cc
	echo "   2. compile gtest main code"
	$(CC) $(OPTIONS) -isystem$(TEST_DIR) -c $(TEST_DIR)/gtest/gtest_main.cc
	echo "   3. make a static library having these two object code"
	ar -rv gtest_main.a gtest-all.o gtest_main.o
	rm *.o

clean:
	rm -rf *.o $(EXE_NAME) gtest_main.a
