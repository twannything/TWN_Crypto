#include <stdlib.h>

#define ECB 1
#define CBC 2
#define OFB 3
#define CTR 4

#define LEA 11
#define ARIA 12
#define SEED 13

unsigned int mo_block_cipher(unsigned char* ct, unsigned char* pt, unsigned char* key, unsigned int keyLen, unsigned int length, unsigned int rem, unsigned int alg, unsigned int mode);
unsigned int dec_ecb_lea(unsigned char* pt, unsigned char* ct, unsigned int* rk, unsigned int length);