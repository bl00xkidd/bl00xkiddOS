#ifndef _SHA224_H
#define _SHA224_H 1

#include <stdint.h>

void sha224(const uint8_t *data, size_t len, uint8_t hash[28]);

#endif