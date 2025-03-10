#ifndef _STRING_H
#define _STRING_H 1

#include <stdarg.h>
#include <stdint.h>
#include <stddef.h>

#define swap(a, b) (a ^= b ^= a ^= b)
#ifndef MAX
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

enum flag_itoa {
    FILL_ZERO = 1,
    PUT_PLUS = 2,
    PUT_MINUS = 4,
    BASE_2 = 8,
    BASE_10 = 16,
};

char *ctos(char s[2], const char c);
void *memset(void *ptr, int value, size_t num);
int memcmp(const void *aptr, const void *bptr, size_t size);
size_t strlen(const char *);
char *strcat(char *d, const char *s);
char *strcpy(char *d, const char *s);
int strcmp(const char *s1, const char *s2);
char *strncat(char *dest, const char *src, size_t n);
char *strncpy(char *dest, const char *src, size_t n);
char *strstr(char *s1, const char *s2);
char *strchr(const char *s, int c);
int strncmp(const char *s1, const char *s2, size_t n);
char *string_tolower(char *string); // Renamed to avoid conflict
char *string_toupper(char *string); // Renamed to avoid conflict
char *sitoa(char *buf, unsigned int num, int width, enum flag_itoa flags);
void my_itoa(char *str, int num, int base); // Renamed to avoid conflict
int vsprintf(char *buf, const char *fmt, va_list va);
int sprintf(char *buf, const char *fmt, ...);
uint32_t my_atoi(const char *str); // Renamed to avoid conflict
double my_atof(char *str); // Renamed to avoid conflict
char *ftoa(char *buf, float f, int precision);
char *strtok(char *str, const char *delim);

#endif // _STRING_H