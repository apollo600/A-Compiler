CC := g++
CFLAGS := -std=c++11
TARGET := ../functional-test/parser.out

SOURCE_DIR := .
BUILD_DIR := ../build

SRCS := $(wildcard $(addprefix $(SOURCE_DIR)/, *.cpp))
SRC_FILES := $(notdir $(SRCS))
OBJS := $(addprefix $(BUILD_DIR)/, $(SRC_FILES:.cpp=.o))
FLEX_BISON_OBJS := $(BUILD_DIR)/parser.tab.o $(BUILD_DIR)/scanner.lex.o

.PHONY: all clean run

all: ${BUILD_DIR} ${TARGET}

run: all
	${TARGET} test_parser.sy

ir: all
	${TARGET} test_parser.sy -o main.ll

clean:
	rm -f parser.out parser.tab.hpp parser.tab.cpp scanner.lex.cpp main.ll main.out
	rm -rf ${BUILD_DIR}

${BUILD_DIR}:
	mkdir ${BUILD_DIR}

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(CC) -c $< -o $@ $(CFLAGS)

parser.tab.cpp: parser.ypp node.h
	# bison $< -d -v --debug
	bison $< -d

scanner.lex.cpp: scanner.l parser.tab.cpp
	flex -o $@ $<

${TARGET}: ${OBJS} $(FLEX_BISON_OBJS)
	${CC} -o $@ ${CFLAGS} $^
