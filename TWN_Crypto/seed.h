#include <string.h>
#include <stdio.h>


unsigned int G(unsigned int X);
void gen_rk(unsigned int* rk, unsigned int* k0, unsigned int* k1);
void F(unsigned int* Co, unsigned int* Do, unsigned int C, unsigned int D, unsigned int k0, unsigned int k1);
void seed_enc(unsigned int* ct, unsigned int* pt);
void seed_dec(unsigned int* dec, unsigned int* enc);