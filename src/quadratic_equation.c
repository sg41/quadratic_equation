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

/**
 * Solves a quadratic equation of the form ax^2 + bx + c = 0 using
 * discriminant calculation. Also check if the equation is linear and solves it
 * if it is.
 */
EquationResult solve_equation(double a, double b, double c) {
  /* Result of the equation solver = no roots by default */
  EquationResult result = {0, NAN, NAN};

  /* Check if the equation is linear. */
  if (a == 0) {
    if (b == 0) return result; /* Nothing to solve, return default result*/

    /* Calculate the linear equation. */
    result.x1 = result.x2 = -c / b;
    result.number_of_roots = 1;
    return result;
  }

  /* Calculate the discriminant. */
  double discriminant = b * b - 4. * a * c;

  if (discriminant > 0) { /*if discriminant>0 we have two roots*/
    double discriminant_sqrt = square_root(discriminant);
    result.x1 = (-b + discriminant_sqrt) / (2. * a);
    result.x2 = (-b - discriminant_sqrt) / (2. * a);
    result.number_of_roots = 2;
  } else if (discriminant == 0) { /*if discriminant=0 we have one root*/
    result.x1 = result.x2 = -b / (2. * a);
    result.number_of_roots = 1;
  } /*if discriminant<0 we have no roots - return default result*/

  return result;
}

/**
 * Calculates the square root of the given number using the binary search
 * algorithm.
 */
double square_root(double x) {
  if (x < 0) return NAN;
  long double l = 0;
  long double r = DBL_MAX;
  while ((r - l) > QE_PRECISION) {
    long double m;
    m = (l + r) / 2;
    if (m * m > x)
      r = m;
    else
      l = m;
  }
  return l;
}
