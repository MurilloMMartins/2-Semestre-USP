#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

typedef struct polynomial poly_t;

poly_t *create_polynomial();
poly_t *polynomial_sum(poly_t *p1, poly_t *p2);
void print_polynomial(poly_t *p);
void destroy_polynomial(poly_t *p);

#endif