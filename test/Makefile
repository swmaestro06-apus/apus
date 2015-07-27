# Google test source code directory
GTEST_DIR = ./gtest-1.7.0

# Compile options
CC = g++
OPTIONS = -lgtest -pthread -g

# Object files
CPP_FILES = factorial.cc factorial_unit_test.cc
OBJS = factorial.o factorial_unit_test.o gtest-all.o gtest_main.o
.SUFFIXES: .h .o .cc
TARGET = factorial_unit_test
EXE_NAME = factorial_unit_test

all: $(TARGET)

$(TARGET): $(CPP_FILES)
	$(CC) $(OPTIONS) -c $(CPP_FILES)
	$(CC) $(OPTIONS) -I${GTEST_DIR} -c ${GTEST_DIR}/src/gtest-all.cc
	$(CC) $(OPTIONS) -I${GTEST_DIR} -c ${GTEST_DIR}/src/gtest_main.cc
	$(CC) $(OPTIONS) $(OBJS) -o $(EXE_NAME)

clean:
	rm -rf *.o $(TARGET)
