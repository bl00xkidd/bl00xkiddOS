#include "../include/calculator.h"
#include "../include/tty.h"
#include "../include/string.h"
#include "../include/math.h"
#include <ctype.h> // Adicionado para usar isdigit

#define MAX_STACK_SIZE 100
static double calc_stack[MAX_STACK_SIZE]; // Declaração fixa
static int calc_top = -1;

void calc_push(double val) {
    if (calc_top >= MAX_STACK_SIZE - 1) {
        printk("Error: Stack overflow\n");
        return;
    }
    calc_stack[++calc_top] = val;
}

double calc_pop() {
    if (calc_top < 0) {
        printk("Error: Stack underflow\n");
        return 0.0;
    }
    return calc_stack[calc_top--];
}

void compute(char *buffer) {
    if (buffer == NULL) {
        printk("Error: Invalid input\n");
        return;
    }

    char *token;
    double a, b;
    char symbol;

    // Reset stack
    calc_top = -1;

    // Tokenize the string buffer into individual tokens
    token = strtok(buffer, " ");
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
            calc_push(atof(token));
        } else {
            if (calc_top < 1) {
                printk("Error: Not enough operands\n");
                return;
            }

            symbol = token[0];
            b = calc_pop();
            a = calc_pop();

            switch (symbol) {
                case '+':
                    calc_push(a + b);
                    break;
                case '-':
                    calc_push(a - b);
                    break;
                case '*':
                    calc_push(a * b);
                    break;
                case '^':
                    calc_push(pow(a, b));
                    break;
                case '/':
                    if (b == 0) {
                        printk("Error: Division by zero\n");
                        return;
                    }
                    calc_push(a / b);
                    break;
                default:
                    printk("Error: Invalid operator '%c'\n", symbol);
                    return;
            }
        }
        token = strtok(NULL, " ");
    }

    if (calc_top != 0) {
        printk("Error: Invalid expression (remaining operands)\n");
        return;
    }

    printk("\nResult: %f\n", calc_pop());
}