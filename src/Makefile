CC = gcc

SRC_DIR = src
BUILD_DIR = $(SRC_DIR)/build
TEST_DIR = $(SRC_DIR)/tests
REPORT_DIR = $(SRC_DIR)/report

CFLAGS = -Wall -Wextra -Werror -std=c11
TEST_FLAGS = -O0 -g -fprofile-arcs -ftest-coverage
LDFLAGS = -lcheck -lsubunit -lm -lgcov -pthread -lrt

LIB_NAME = s21_decimal.a
LIB_PATH = $(BUILD_DIR)/$(LIB_NAME)

ARITHMETIC_SRCS = $(wildcard $(SRC_DIR)/arithmetic/*.c)
COMPARISON_SRCS = $(wildcard $(SRC_DIR)/comparison/*.c)
CONVERTORS_SRCS = $(wildcard $(SRC_DIR)/convertors/*.c)
UTILS_SRCS = $(wildcard $(SRC_DIR)/utils/*.c)

SRC_FILES = $(ARITHMETIC_SRCS) $(COMPARISON_SRCS) $(CONVERTORS_SRCS) $(UTILS_SRCS)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRC_FILES))

TEST_SRCS = $(wildcard $(TEST_DIR)/test_*.c)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/%.test.o, $(TEST_SRCS))

.PHONY: all clean test coverage gcov_report

all: $(LIB_PATH)

$(LIB_PATH): $(OBJ_FILES)
	ar rcs $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.test.o: $(TEST_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(TEST_FLAGS) -c $< -o $@

test_runner: $(TEST_OBJS) $(LIB_PATH)
	$(CC) $(TEST_FLAGS) $^ -o $@ $(LDFLAGS)

test: test_runner
	./test_runner

gcov_report: test
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory $(REPORT_DIR)
	@echo "Open $(REPORT_DIR)/index.html"

clean:
	rm -rf $(BUILD_DIR) *.gcno *.gcda *.gcov *.info $(REPORT_DIR) test_runner
