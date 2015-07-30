CC = g++
PRJ_HOME = ..
INCLUDE_DIR = $(PRJ_HOME)/include
SRC_DIR = $(PRJ_HOME)/src
TEST_DIR = $(PRJ_HOME)/test

OPTIONS = -pthread -g
CPP_FILE = factorial.cc
TEST_FILE = factorial_unit_test.cc
OBJS = factorial.o factorial_unit_test.o gtest-all.o gtest_main.o

.SUFFIXES: .h .o .cc
TARGET = factorial_unit_test
EXE_NAME = factorial_unit_test

all: $(TARGET)

$(TARGET): $(CPP_FILES)
	echo "1. compile source code"
	$(CC) $(OPTIONS) -c $(SRC_DIR)/sample/factorial.cc
	echo "2. compile test source code"
	$(CC) $(OPTIONS) -isystem$(TEST_DIR) -I$(INCLUDE_DIR) -c $(TEST_DIR)/factorial_unit_test.cc
	echo "3. compile gtest-all code"
	$(CC) $(OPTIONS) -isystem$(TEST_DIR) -c $(TEST_DIR)/gtest/gtest-all.cc
	echo "4. compile gtest main code"
	$(CC) $(OPTIONS) -isystem$(TEST_DIR) -c $(TEST_DIR)/gtest_main.cc
	echo "5. make final executable file"
	$(CC) $(OPTIONS) $(OBJS) -o $(EXE_NAME)

clean:
	rm -rf *.o $(TARGET)

