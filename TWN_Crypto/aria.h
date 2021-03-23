#include <stdio.h>
#include <string.h>


typedef unsigned char byte;

void left_shift(byte* x, int l);
void right_shift(byte* x, int l);
void ROR(byte* x, int r);
void ROL(byte* x, int r);
void Add_Round_Key(byte* state, byte* w);
void LT(byte* state);
void inv_LT(byte* state);
void SubstLayer(byte* state, int eo);
void DiffLayer(byte* state);
void F_o(byte* state, byte* k);
void F_e(byte* state, byte* k);
void Key_expansion(byte* w, byte* key, unsigned int keyLen);
void aria_enc(byte* state, byte* out, byte* key, unsigned int keyLen);
void aria_dec(byte* state, byte* out, byte* key, unsigned int keyLen);
