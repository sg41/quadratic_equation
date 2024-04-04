#include "quadratic_equation.h"

#include <math.h>

EquationResult solve_equation(double a, double b, double c) {
  EquationResult result;
  double discriminant = b * b - 4 * a * c;

  if (discriminant > 0) {
    result.x1 = (-b + sqrt(discriminant)) / (2 * a);
    result.x2 = (-b - sqrt(discriminant)) / (2 * a);
    result.number_of_roots = 2;
  } else if (discriminant == 0) {
    result.x1 = result.x2 = -b / (2 * a);
    result.number_of_roots = 1;
  } else {
    result.x1 = result.x2 = NAN;
    result.number_of_roots = 0;
  }

  return result;
}
