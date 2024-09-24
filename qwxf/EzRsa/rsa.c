#include "rsa.h"

#include <stdio.h>
#include <string.h>

static void subM(RSAPublicKey key, uint32_t* a) {
  int64_t A = 0;
  int i;
  for (i = 0; i < key->len; ++i) {
    A += (uint64_t)a[i] - key->n[i];
    a[i] = (uint32_t)A;
    A >>= 32;
  }
}

static int geM(RSAPublicKey key, const uint32_t* a) {
  int i;
  for (i = key->len; i;) {
    --i;
    if (a[i] < key->n[i]) return 0;
    if (a[i] > key->n[i]) return 1;
  }
  return 1;
}

static void montMulAdd(RSAPublicKey key, uint32_t* c, const uint32_t a,
                       const uint32_t* b) {
  uint64_t A = (uint64_t)a * b[0] + c[0];
  uint32_t d0 = (uint32_t)A * key->n0inv;
  uint64_t B = (uint64_t)d0 * key->n[0] + (uint32_t)A;
  int i;

  for (i = 1; i < key->len; ++i) {
    A = (A >> 32) + (uint64_t)a * b[i] + c[i];
    B = (B >> 32) + (uint64_t)d0 * key->n[i] + (uint32_t)A;
    c[i - 1] = (uint32_t)B;
  }

  A = (A >> 32) + (B >> 32);

  c[i - 1] = (uint32_t)A;

  if (A >> 32) {
    subM(key, c);
  }
}

static void montMul(RSAPublicKey key, uint32_t* c, const uint32_t* a,
                    const uint32_t* b) {
  int i;
  for (i = 0; i < key->len; ++i) c[i] = 0;
  for (i = 0; i < key->len; ++i) montMulAdd(key, c, a[i], b);
}

static void modpowDec(RSAPublicKey key, uint8_t* inout) {
  uint32_t a[RSANUMWORDS];
  uint32_t aR[RSANUMWORDS];
  uint32_t aaR[RSANUMWORDS];
  uint32_t* aaa = aaR;
  int i;

  for (i = 0; i < key->len; ++i) {
    uint32_t tmp = (inout[((key->len - 1 - i) * 4) + 0] << 24) |
                   (inout[((key->len - 1 - i) * 4) + 1] << 16) |
                   (inout[((key->len - 1 - i) * 4) + 2] << 8) |
                   (inout[((key->len - 1 - i) * 4) + 3] << 0);
    a[i] = tmp;
  }

  montMul(key, aR, a, key->rr);
  for (i = 0; i < 16; i += 2) {
    montMul(key, aaR, aR, aR);
    montMul(key, aR, aaR, aaR);
  }
  montMul(key, aaa, aR, a);

  if (geM(key, aaa)) subM(key, aaa);

  for (i = key->len - 1; i >= 0; --i) {
    uint32_t tmp = aaa[i];
    *inout++ = tmp >> 24;
    *inout++ = tmp >> 16;
    *inout++ = tmp >> 8;
    *inout++ = tmp >> 0;
  }
}

static void modpowEnc(RSAPrivateKey k, uint8_t* inout) {
  RSAPublicKey key = (RSAPublicKey)k;
  uint32_t a[RSANUMWORDS];
  uint32_t aR[RSANUMWORDS];
  uint32_t aaR[RSANUMWORDS];
  uint32_t t[RSANUMWORDS];
  uint32_t* aaa = aaR;
  int i = 0, j = 0;

  for (i = 0; i < key->len; ++i) {
    uint32_t tmp = (inout[((key->len - 1 - i) * 4) + 0] << 24) |
                   (inout[((key->len - 1 - i) * 4) + 1] << 16) |
                   (inout[((key->len - 1 - i) * 4) + 2] << 8) |
                   (inout[((key->len - 1 - i) * 4) + 3] << 0);
    a[i] = tmp;
  }

  montMul(key, aR, a, key->rr);
  montMul(key, t, a, key->rr);
  int d_dword_len = k->d_bit_len / 32, d_bit_rem = k->d_bit_len % 32;
  for (i = d_bit_rem - 2; i >= 0; i--) {
    montMul(key, aaR, t, t);
    memcpy(t, aaR, RSANUMBYTES);

    if (k->d[d_dword_len] & (1 << i)) {
      montMul(key, aaR, aR, t);
      memcpy(t, aaR, RSANUMBYTES);
    }
  }
  for (i = d_dword_len - 1; i >= 0; i--) {
    for (j = 31; j >= 0; --j) {
      montMul(key, aaR, t, t);
      memcpy(t, aaR, RSANUMBYTES);

      if (k->d[i] & (1 << j)) {
        montMul(key, aaR, aR, t);
        memcpy(t, aaR, RSANUMBYTES);
      }
    }
  }
  uint32_t one[RSANUMWORDS] = {0};
  one[0] = 1;
  montMul(key, aaa, t, one);

  if (geM(key, aaa)) subM(key, aaa);

  for (i = key->len - 1; i >= 0; --i) {
    uint32_t tmp = aaa[i];
    *inout++ = tmp >> 24;
    *inout++ = tmp >> 16;
    *inout++ = tmp >> 8;
    *inout++ = tmp >> 0;
  }
}

int RSA2048_Encrypt(RSAPrivateKey key, const uint8_t* pIn, const int len,
                    uint8_t* pOut) {
  uint8_t buf[RSANUMBYTES];
  int i;

  if (key->len != RSANUMWORDS) return 0;

  if (len != sizeof(buf)) return 0;

  if (pOut == 0) return 0;

  for (i = 0; i < len; ++i) buf[i] = pIn[i];

  if (key->d == NULL) {
    puts("Invalid d");
    return 0;
  }
  if (key->d_bit_len == 0) {
    puts("Invalid d_bit_len");
    return 0;
  }

#ifdef DECODE_TEST
  modpowEnc(key, buf);
#else
  puts("Not implemented yet");
#endif  // DECODE_TEST

  for (i = 0; i < len; ++i) pOut[i] = buf[i];
  return 1;
}

int RSA2048_Decrypt(RSAPublicKey key, const uint8_t* pEncryptedData,
                    const int len, uint8_t* pOut) {
  uint8_t buf[RSANUMBYTES];
  if (key->len != RSANUMWORDS) return 0;

  if (len != sizeof(buf)) return 0;

  if (pOut == 0) return 0;

  for (int i = 0; i < len; ++i) buf[i] = pEncryptedData[i];

  modpowDec(key, buf);
  for (int i = 0; i < len; ++i) pOut[i] = buf[i];

  return 1;
}