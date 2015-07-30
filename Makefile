CC = g++
PRJ_HOME = .
OPTIONS = -g
TARGET = apus
.SUFFIXES: .h .o .cpp

INCLUDE = $(PRJ_HOME)/include
SRC_DIR = $(PRJ_HOME)/src
SRC_FILES = $(SRC_DIR)/common/common.cpp 
SRC_FILES += $(SRC_DIR)/utils/BinaryReader.cpp
MAIN_CPP = $(SRC_DIR)/Main.cpp
OBJS = common.o BinaryReader.o Main.o

all: $(TARGET)

$(TARGET):
	$(CC) $(OPTIONS) -I$(INCLUDE) -c $(SRC_FILES)
	$(CC) $(OPTIONS) -I$(INCLUDE) -c $(MAIN_CPP)
	$(CC) $(OBJS) -o apus

clean: 
	rm *.o apus
