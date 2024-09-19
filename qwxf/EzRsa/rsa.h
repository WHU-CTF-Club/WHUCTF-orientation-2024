#ifndef _RSA_H
#define _RSA_H

#include <stddef.h>
#include <stdint.h>

#define RSANUMBYTES 256
#define RSANUMWORDS (RSANUMBYTES / sizeof(uint32_t))

typedef struct RSAPrivateKeyInstance {
  int len;
  uint32_t n0inv;
  uint32_t n[RSANUMWORDS];
  uint32_t rr[RSANUMWORDS];
  uint32_t d[RSANUMWORDS];
  uint32_t d_bit_len;
} RSAPrivateKeyInstance;

typedef const RSAPrivateKeyInstance* const RSAPrivateKey;

typedef struct RSAPublicKeyInstance {
  int len;
  uint32_t n0inv;
  uint32_t n[RSANUMWORDS];
  uint32_t rr[RSANUMWORDS];
} RSAPublicKeyInstance;

typedef const RSAPublicKeyInstance* const RSAPublicKey;

int RSA2048_Encrypt(RSAPrivateKey key, const uint8_t*, int, uint8_t*);
int RSA2048_Decrypt(RSAPublicKey key, const uint8_t*, int, uint8_t*);

#endif