# Solve Equation

This is a C library for solving equations of the form ax^2 + bx + c = 0.

## Building

* To build the library, run the following command:

  ```
  make
  ```

  This will create a `libsolve_equation.a` library file in the current directory.

* To build the test program, run the following command:

  ```
  make tests
  ```

  This will create a `test` executable in the current directory and run it to test the library.
  >note: The test program uses the [check](https://libcheck.github.io/check/) framework for unit testing. You will need to install `check` to run the test program.

* To check library source code for style errors, and then run the test program, run the following command:
  ```
  make check
  ```

* To check the library for memory leaks, run the following command:

  ```
  make leaks
  ```

  This will create a `leaks.log` file in the current directory and run the test program to check for memory leaks.

* To check unit tests coverage, run the following command:
  ```
  make gcov_report
  ```
  This will create a `report` directory in the current directory and open a web browser to display the test coverage report.

* To clean up the build directory, run the following command:

  ```
  make clean
  ```

## Usage

To use the library, include the `solve_equation.h` header file and link against the `libsolve_equation.a` library file.

```c
#include "solve_equation.h"
#include <stdio.h>

int main() {
  EquationResult result = solve_equation(1, 2, 3);
  printf("x1: %f\n", result.x1);
  printf("x2: %f\n", result.x2);
  return 0;
}
```

## License

This library is licensed under the BSD 3-Clause License. See the [LICENSE](LICENSE) file for more information.