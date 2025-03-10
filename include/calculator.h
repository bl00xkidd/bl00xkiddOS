#ifndef _CALCULATOR_H
#define _CALCULATOR_H 1

#define MAX_STACK_SIZE 100

// Declarações de função sem blocos condicionais inválidos
void calc_push(double val);
double calc_pop();
void compute(char *buffer); // Declaração direta da função

#endif // _CALCULATOR_H