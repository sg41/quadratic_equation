#ifndef QUADRATIC_EQUATION_H
#define QUADRATIC_EQUATION_H

typedef struct {
  int number_of_roots;
  double x1;
  double x2;
} EquationResult;

EquationResult solve_equation(double a, double b, double c);
#endif