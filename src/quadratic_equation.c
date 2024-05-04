/**
 * @file quadratic_equation.c
 * @author Sergey Gorbatenko (sg41@mail.ru)
 * @brief This file is part of the quadratic equation solver library.
 *  It contains the implementation of the quadratic equation solver function
 *  solve_equation.
 * @version 0.1
 * @date 2024-05-04
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "quadratic_equation.h"

#include <float.h>
#include <math.h>

EquationResult solve_equation(double a, double b, double c) {
  EquationResult result; /* Result of the equation solver. */

  /* Calculate the discriminant. */
  double discriminant = b * b - 4 * a * c;

  /*
   * Solve the equation based on the discriminant.
   * we dont check a == 0 because it should be non-zero by the rules of the
   * quadratic equation
   */
  if (discriminant > 0) { /*if discriminant>0 we have two roots*/
    // result.x1 = (-b + sqrt(discriminant)) / (2 * a);
    // result.x2 = (-b - sqrt(discriminant)) / (2 * a);
    result.x1 = (-b + square_root(discriminant)) / (2 * a);
    result.x2 = (-b - square_root(discriminant)) / (2 * a);
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

EquationResult solve_equation_safe(int a, int b, int c) {
  EquationResult result = {0, NAN, NAN};
  if (a != 0)
    result = solve_equation((double)a, (double)b, (double)c);
  else if (b != 0) {
    result.number_of_roots = 1;
    result.x1 = result.x2 = -c / b;
  };
  return result;
}

double square_root(double x) {
  if (x < 0) return NAN;
  long double l = 0;
  long double r = DBL_MAX;
  long double m;
  while (fabsl(r - l) > PRECISION) {
    m = (l + r) / 2;
    if (m * m > x)
      r = m;
    else
      l = m;
  }
  return l;
}
