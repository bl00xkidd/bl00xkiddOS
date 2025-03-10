#ifndef _MATH_H
#define _MATH_H 1

#include <stdint.h> // Add this line to define uint32_t

// Constantes
#ifndef PI
#define PI 3.14159265358979323846
#endif

#ifndef EPS
#define EPS 1.073741824e-16
#endif

#ifndef MAX
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#endif

// Protótipos essenciais
double pow(double x, double y);
double sqrt(double x);
double sin(double x);
#define MIN(a, b)   (((a) < (b)) ? (a) : (b))
#define MAX(a, b)   (((a) > (b)) ? (a) : (b))

// Macro corrigida (sem 'if' inválidos e backslashes desnecessários)
#define type_name(x) _Generic((x),                     \
    short int:                "short int",            \
    unsigned short int:       "unsigned short int",   \
    int:                      "int",                  \
    unsigned int:             "unsigned int",         \
    long int:                 "long int",             \
    unsigned long int:        "unsigned long int",    \
    long long int:            "long long int",        \
    unsigned long long int:   "unsigned long long int", \
    float:                    "float",                \
    double:                   "double",               \
    long double:              "long double",          \
    typeof(int*):             "pointer to int",       \
    typeof(void*):            "pointer to void",      \
    default:                  "other")

// Protótipos de função
double machine_eps(double x);
uint32_t fact(uint32_t n); // uint32_t is now defined
double abs(double x);
double ipow(double x, uint32_t n); // uint32_t is now defined
double sqrt(double x);
double inv_sqrt(double x);
double sin(double x);
double cos(double x);
double tan(double x);
double asin(double x);
double acos(double x);
double atan(double x);
double sinh(double x);
double cosh(double x);
double tanh(double x);
double asinh(double x);
double acosh(double x);
double atanh(double x);
double exp(double x);
double ln(double x);
uint32_t log2(uint32_t x); // uint32_t is now defined
double log10(double x);
double log(double x, double y);

#endif // _MATH_H