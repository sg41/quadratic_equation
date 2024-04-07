# Test Suite

This directory contains the test suite for the quadratic equation library. Be sure `check library` is installed before running the tests. To install `check library`, follow the instructions [here](https://libcheck.github.io/check/web/install.html).

.check files are used as source to generate the test suite. To generate the test suite, run the following command from the project root directory:

```
make testgen
```

This will generate the `solve_equation_test.c` file in the `tests` directory.

To run the test suite, run the following command from the project root directory:

```
make tests
```

This will compile the test suite and run the tests.

The test suite uses the [check](https://libcheck.github.io/check/) framework for unit testing. You will need to install `check` to run the test suite.

To check the test suite for style errors, and then run the tests, run the following command:

```
make check
```

To check the test suite for memory leaks, run the following command:

```
make leaks
```

This will create a `leaks.log` file in the current directory and run the tests to check for memory leaks.

To clean up the build directory, run the following command:

```
make clean
```

This will remove all object files, libraries, report, and log files.

> Note: All `make` commands should be run from the project root directory.
