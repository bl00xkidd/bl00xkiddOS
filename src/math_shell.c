#include "math_shell.h"

extern int default_font_color; // Explicitly declare as int

boolean math_func(char *buffer) {
    if (buffer == NULL || strlen(buffer) == 0) {
        return false;
    }

    const char *math_functions[] = {
        "fact", "exp", "ln", "log10", "sqrt", "abs",
        "asinh", "acosh", "atanh", "asin", "acos", "atan",
        "sin", "cos", "tan", "sinh", "cosh", "tanh",
        "pow", "log", "srand", "rand"
    };

    const int num_functions = sizeof(math_functions) / sizeof(math_functions[0]);

    for (int i = 0; i < num_functions; i++) {
        if (strstr(buffer, math_functions[i]) != NULL) {
            return true;
        }
    }

    return false;
}

void math_shell(char *buffer) {
    if (buffer == NULL || strlen(buffer) == 0) {
        terminal_set_colors(COLOR_BLUE, COLOR_BLACK);
        printk("\nInvalid input");
        terminal_set_colors(default_font_color, COLOR_BLACK);
        return;
    }

    char parser[MAX_PARSER_SIZE] = {0};
    char buff[32] = {0};  // For number conversion
    double num, n;

    if (strstr(buffer, "fact(") != NULL) {
        uint32_t val;
        char *p = strstr(buffer, "fact(");
        p += strlen("fact(");
        val = parse_int(p, ')');
        if (val != (uint32_t)NULL) {
            printk("\n%d", fact(val));
        } else {
            terminal_set_colors(COLOR_BLUE, COLOR_BLACK);
            printk("\nParsing error");
            terminal_set_colors(default_font_color, COLOR_BLACK);
        }
        return;
    }

    // Handle single argument functions
    const char *single_arg_funcs[] = {
        "exp(", "ln(", "log10(", "sqrt(", "abs(",
        "asinh(", "acosh(", "atanh(", "asin(", "acos(", "atan(",
        "sin(", "cos(", "tan(", "sinh(", "cosh(", "tanh("
    };

    const double (*single_arg_ops[])(double) = {
        exp, ln, log10, sqrt, abs,
        asinh, acosh, atanh, asin, acos, atan,
        sin, cos, tan, sinh, cosh, tanh
    };

    const int num_single_args = sizeof(single_arg_funcs) / sizeof(single_arg_funcs[0]);

    for (int i = 0; i < num_single_args; i++) {
        if (strstr(buffer, single_arg_funcs[i]) != NULL) {
            char *p = strstr(buffer, single_arg_funcs[i]);
            p += strlen(single_arg_funcs[i]);
            num = parse_float(p, ')');
            if (num != EPS) {
                printk("\n");
                printk(ftoa(buff, single_arg_ops[i](num), 6));
            } else {
                terminal_set_colors(COLOR_BLUE, COLOR_BLACK);
                printk("\nParsing error");
                terminal_set_colors(default_font_color, COLOR_BLACK);
            }
            return;
        }
    }

    // Handle two argument functions
    if (strstr(buffer, "pow(") != NULL) {
        char *p = strstr(buffer, "pow(");
        p += strlen("pow(");
        num = parse_float(p, ',');
        if (num != EPS) {
            while (*p != ',') p++;
            p++;
            n = parse_float(p, ')');
            printk("\n");
            printk(ftoa(buff, pow(num, n), 6));
        } else {
            terminal_set_colors(COLOR_BLUE, COLOR_BLACK);
            printk("\nParsing error");
            terminal_set_colors(default_font_color, COLOR_BLACK);
        }
        return;
    }

    if (strstr(buffer, "log(") != NULL) {
        char *p = strstr(buffer, "log(");
        p += strlen("log(");
        num = parse_float(p, ',');
        if (num != EPS) {
            while (*p != ',') p++;
            p++;
            n = parse_float(p, ')');
            printk("\n");
            printk(ftoa(buff, log(num, n), 6));
        } else {
            terminal_set_colors(COLOR_BLUE, COLOR_BLACK);
            printk("\nParsing error");
            terminal_set_colors(default_font_color, COLOR_BLACK);
        }
        return;
    }

    // Handle special functions
    if (strcmp(buffer, "srand()") == 0) {
        printk("\nGenerated seed for random number generator");
        srand();
        return;
    }

    if (strcmp(buffer, "rand()") == 0) {
        printk("\n");
        printk(ftoa(buff, rand(), 6));
        return;
    }

    terminal_set_colors(COLOR_BLUE, COLOR_BLACK);
    printk("\nUnknown function");
    terminal_set_colors(default_font_color, COLOR_BLACK);
}