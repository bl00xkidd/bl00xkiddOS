#ifndef _MATH_SHELL_H
#define _MATH_SHELL_H

#include "../include/math.h"
#include "../include/limits.h"
#include "../include/tty.h"
#include "../include/string.h"
#include "../include/parsing.h"
#include "../include/random.h"

#define MAX_PARSER_SIZE 1024

// Function declarations
boolean math_func(char *buffer);
void math_shell(char *buffer);

#endif // _MATH_SHELL_H