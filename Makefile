CC						=gcc
CFLAGS					=-std=c11 -Wall -Werror -Wextra
CLEAN					=rm -rf
uname_S 				:= $(shell uname -s)
ifeq ($(uname_S), Linux)
	CHECK_LIBS			=-lcheck -lm -lpthread -lsubunit -lrt
	LEAKS				=valgrind --undef-value-errors=yes $(BUILD_DIR)/test
else
	CHECK_LIBS			=-lcheck -lm -lpthread
	LEAKS				=CK_FORK=no leaks --atExit -- $(BUILD_DIR)/test
endif
SOURCES					=*.c
SRC_DIR					=./
INCLUDES				=./

HEADERS					=*.h
OBJECTS					=*.o
TEST					=solve_equation_test.c
TEST_DIR				=./tests

DEBUG_DIR				=./debug
DEBUG_PROG				=debug.out

BUILD_DIR				=./
LIB_NAME				=solve_equation
LIB_FILE_NAME			=lib$(LIB_NAME).a

$(LIB_FILE_NAME): clean $(SRC_DIR)/$(SOURCES) $(SRC_DIR)/$(HEADERS)
	$(CC) $(CFLAGS) -g -c $(SRC_DIR)/$(SOURCES)
	ar rc $(LIB_FILE_NAME) $(OBJECTS)
	$(CLEAN) $(OBJECTS)

all: clean $(LIB_FILE_NAME) check gcov_report

rebuild: clean all

clean:
	@$(CLEAN) $(OBJECTS) *.a *.gcno *.gcda *.gcov *.info
	@$(CLEAN) $(BUILD_DIR)/$(OBJECTS) $(BUILD_DIR)/*.a $(BUILD_DIR)/$(TEST)
	@$(CLEAN) $(BUILD_DIR)/report/
	@$(CLEAN) $(TEST_DIR)/$(TEST)
	@$(CLEAN) $(DEBUG_PROG)
	@$(CLEAN) ./leaks.log

tests: test

test: clean $(LIB_FILE_NAME) testgen
	$(CC) $(CFLAGS) -g $(TEST_DIR)/$(TEST) $(INCLUDES:%=-I %) -L./ -l$(LIB_NAME) $(CHECK_LIBS) -o $(BUILD_DIR)/$@
	-$(BUILD_DIR)/$@	

gcov_report: CFLAGS += --coverage
gcov_report: CHECK_LIBS += -lgcov
gcov_report: clean test
	$(CLEAN) $(OBJ)
	-$(BUILD_DIR)/$(TEST)
	gcov *.gcda
	lcov -t "gcov_report" -o gcov_report.info -c -d .
	-mkdir $(BUILD_DIR)/report
	genhtml -o $(BUILD_DIR)/report gcov_report.info
	$(CLEAN) $(TEST_DIR)/$(TEST)
	open $(BUILD_DIR)/report/index.html

testgen: $(TEST_DIR)/*.check
	$(CLEAN) $(TEST_DIR)/$(TEST)
	checkmk clean_mode=1 $(TEST_DIR)/*.check > $(TEST_DIR)/$(TEST)

check: cpplint cppcheck test

cpplint:
	clang-format -i -style=google -verbose $(SRC_DIR)/$(SOURCES)

cppcheck:
	cppcheck --std=c11 --enable=all --suppress=missingIncludeSystem --suppress=unusedFunction $(SRC_DIR)/$(SOURCES)

leaks: clean test
	$(LEAKS) > leaks.log 2>&1
	grep "ERROR SUMMARY" leaks.log

valgrind: leaks

.PHONY: testgen clean