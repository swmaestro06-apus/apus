CC = g++
AR = ar

TEST_DIR = ..
GTEST_DIR = $(TEST_DIR)/gtest
YACC_DIR = $(TEST_DIR)/../src

TEST_SRC = $(wildcard *.cpp)
TEST_OBJ = $(TEST_SRC:.cpp=.o)
TEST_EXE = unit_test

CFLAGS = -pthread -g
LDFLAGS = -I$(TEST_DIR)

all: $(TEST_EXE)
	./$(TEST_EXE)

$(TEST_EXE): $(TEST_OBJ) $(YACC_DIR)/y.tab.o $(YACC_DIR)/lex.yy.o libgtest_main.a
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $^

$(TEST_OBJ): %.o: %.cpp ${GTEST_DIR}/gtest.h
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ -c $<

# make libgtest_main.a, which is a static library that contains gtest code
libgtest_main.a: $(GTEST_DIR)/gtest-all.cc $(GTEST_DIR)/gtest_main.cc $(GTEST_DIR)/gtest.h
	$(CC) $(CFLAGS) $(LDFLAGS) -c $(GTEST_DIR)/gtest-all.cc
	$(CC) $(CFLAGS) $(LDFLAGS) -c $(GTEST_DIR)/gtest_main.cc
	$(AR) -rv libgtest_main.a gtest-all.o gtest_main.o

# clean all intermidate files and executable file
clean:
	rm -rf *.o $(TEST_EXE) libgtest_main.a
