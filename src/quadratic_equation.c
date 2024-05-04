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
  EquationResult result = {0, NAN, NAN}; /* Result of the equation solver. */

  /* Check if the equation is linear. */
  if (a == 0) {
    if (b == 0) return result; /* Nothing to solve*/
    /* Calculate the linear equation. */
    result.x1 = result.x2 = -c / b;
    result.number_of_roots = 1;
    return result;
  }

  /* Calculate the discriminant. */
  double discriminant = b * b - 4 * a * c;

  if (discriminant > 0) { /*if discriminant>0 we have two roots*/
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

/**
 * Calculates the square root of the given number using the binary search
 * algorithm.
 */
double square_root(double x) {
  if (x < 0) return NAN;
  long double l = 0;
  long double r = DBL_MAX;
  while (fabsl(r - l) > PRECISION) {
    long double m;
    m = (l + r) / 2;
    if (m * m > x)
      r = m;
    else
      l = m;
  }
  return l;
}
