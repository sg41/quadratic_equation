# quadratic_equation/Makefile
#
# This Makefile is used to compile and test the quadratic_equation project.
#
# The main targets are:
# - all: compile the library and run tests
# - rebuild: clean everything and rebuild everything
# - clean: remove object files, libraries, report and log files
# - tests: alias for test
# - test: compile and run tests
# - gcov_report: generate a gcov report (requires gcov and lcov)
# - testgen: generate units tests .c files from .check files using check framework
# - check: run cpplint and cppcheck
# - cpplint: format C files with clang-format
# - cppcheck: static analysis of C files with cppcheck
# - leaks: run tests and check for memory leaks with valgrind or leaks
# - valgrind: alias for leaks
#
# All paths are relative to the Makefile location.
#
# To customize this Makefile:
# - Change CC, CFLAGS according to your needs.
# - Change SRC_DIR, TEST_DIR, DEBUG_DIR, BUILD_DIR, and LIB_NAME.
# - Change CHECK_LIBS and LEAKS according to your needs.
#
# Note: this Makefile assumes that the .h files are in the same directory
# as the .c files. If this is not the case, you will need to change the
# INCLUDES variable.
CC						=gcc
CFLAGS					=-std=c11 -Wall -Werror -Wextra -g
CLEAN					=rm -rf
CHECK_LIBS				=$(shell pkg-config --libs check)
CFLAGS					+=$(shell pkg-config --cflags check)


SOURCES					=*.c
SRC_DIR					=./src
INCLUDES				=./src
HEADERS					=*.h
OBJECTS					=*.o

TEST_SOURCE				=solve_equation_test.c
TEST_DIR				=./tests
TEST_PROG				=test

DOCS_DIR				=./docs
BUILD_DIR				=./
LIB_NAME				=solve_equation
LIB_FILE_NAME			=lib$(LIB_NAME).a

uname_S 				:= $(shell uname -s)
ifeq ($(uname_S), Linux)
	LEAKS				=valgrind --undef-value-errors=yes $(BUILD_DIR)/$(TEST_PROG)
else
	LEAKS				=CK_FORK=no leaks --atExit -- $(BUILD_DIR)/$(TEST_PROG)
endif

$(LIB_FILE_NAME): clean $(SRC_DIR)/$(SOURCES) $(SRC_DIR)/$(HEADERS)
	$(CC) $(CFLAGS) -c $(SRC_DIR)/$(SOURCES)
	ar rc $(LIB_FILE_NAME) $(OBJECTS)
	$(CLEAN) $(OBJECTS)

all: clean $(LIB_FILE_NAME) check

rebuild: clean all

clean:
	@$(CLEAN) $(OBJECTS) *.a *.gcno *.gcda *.gcov *.info
	@$(CLEAN) $(BUILD_DIR)/$(OBJECTS) $(BUILD_DIR)/*.a $(BUILD_DIR)/$(TEST_PROG)
	@$(CLEAN) $(BUILD_DIR)/report/
	@$(CLEAN) $(BUILD_DIR)/$(TEST_PROG)
	@$(CLEAN) $(TEST_DIR)/$(TEST_SOURCE)
	@$(CLEAN) $(DOCS_DIR)
	@$(CLEAN) ./leaks.log

tests: $(TEST_PROG)
	-$(BUILD_DIR)/$<	

$(TEST_PROG): clean $(LIB_FILE_NAME) testgen
	$(CC) $(CFLAGS) $(TEST_DIR)/$(TEST_SOURCE) $(INCLUDES:%=-I %) -L./ -l$(LIB_NAME) $(CHECK_LIBS) -o $(BUILD_DIR)/$@

gcov_report: CFLAGS += --coverage
gcov_report: CHECK_LIBS += -lgcov
gcov_report: clean $(TEST_PROG)
	$(CLEAN) $(OBJ)
	gcov *.gcda
	lcov -t "gcov_report" -o gcov_report.info -c -d .
	-mkdir $(BUILD_DIR)/report
	genhtml -o $(BUILD_DIR)/report gcov_report.info
	$(CLEAN) $(TEST_DIR)/$(TEST_SOURCE)

show_coverage: gcov_report
	open $(BUILD_DIR)/report/index.html

testgen: $(TEST_DIR)/*.check
	$(CLEAN) $(TEST_DIR)/$(TEST_SOURCE)
	checkmk clean_mode=1 $(TEST_DIR)/includes.h $(TEST_DIR)/*.check > $(TEST_DIR)/$(TEST_SOURCE)

check: cpplint cppcheck $(TEST_PROG)

cpplint:
	clang-format -i -style=google -verbose $(SRC_DIR)/$(SOURCES)

cppcheck:
	cppcheck --std=c11 --enable=all --suppress=missingIncludeSystem --suppress=unusedFunction $(SRC_DIR)/$(SOURCES)

leaks: clean $(TEST_PROG)
	$(LEAKS) > leaks.log

valgrind: leaks

docs: Doxyfile.conf $(SRC_DIR)/$(SOURCES) $(SRC_DIR)/$(HEADERS) README.md
	doxygen Doxyfile.conf

show_docs: docs 
	open $(DOCS_DIR)/html/index.html

.PHONY: testgen clean
