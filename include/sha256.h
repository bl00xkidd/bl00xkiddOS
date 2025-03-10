#ifndef _SHA256_H
#define _SHA256_H 1

#include <stdint.h>

// Function declarations for SHA-256
void sha256(const uint8_t *data, size_t len, uint8_t hash[32]);

#endif // _SHA256_H