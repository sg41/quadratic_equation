/**
 * Source file for the quadratic equation solver.
 *
 *  This file is part of the quadratic equation solver library.
 *  It contains the implementation of the quadratic equation solver function
 *  solve_equation.
 *
 */
#include "quadratic_equation.h"

#include <math.h>

EquationResult solve_equation(double a, double b, double c) {
  EquationResult result; /* Result of the equation solver. */

  /* Calculate the discriminant. */
  double discriminant = b * b - 4 * a * c;

  /**
   * Solve the equation based on the discriminant.
   * we dont check a == 0 because it should be non-zero by the rules of the
   * quadratic equation
   */
  if (discriminant > 0) { /*if discriminant>0 we have two roots*/
    result.x1 = (-b + sqrt(discriminant)) / (2 * a);
    result.x2 = (-b - sqrt(discriminant)) / (2 * a);
    result.number_of_roots = 2;
  } else if (discriminant == 0) { /*if discriminant=0 we have one root*/
    result.x1 = result.x2 = -b / (2 * a);
    result.number_of_roots = 1;
  } else { /*if discriminant<0 we have no roots*/
    result.x1 = result.x2 = NAN;
    result.number_of_roots = 0;
  }

  return result;
}
