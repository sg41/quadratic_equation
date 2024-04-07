/**
 * Header file for the quadratic equation solver.
 */
#ifndef QUADRATIC_EQUATION_H
#define QUADRATIC_EQUATION_H

/**
 * Data structure for the result of the quadratic equation solver.
 */
typedef struct {
  int number_of_roots; /* Number of roots found. */
  double x1;           /* Value of the first root. */
  double x2;           /* Value of the second root. */
} EquationResult;

/**
 * Solves a quadratic equation of the form ax^2 + bx + c = 0.
 *
 * @param a The coefficient of the x^2 term. Must be non-zero.
 * @param b The coefficient of the x term.
 * @param c The constant term.
 *
 * @return An EquationResult struct containing the number of roots and the
 * values of the roots.
 *
 * The EquationResult struct has the following fields:
 * - int number_of_roots: The number of real roots.
 * - double x1: The value of the first root.
 * - double x2: The value of the second root.
 * If the number of roots is 0, the values of x1 and x2 are NAN.
 * If the number of roots is 1, then x1 == x2, and contains the
 * value of the root.
 * Precision 1e-7
 */
EquationResult solve_equation(double a, double b, double c);
#endif