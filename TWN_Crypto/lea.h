#pragma once
#include <stdio.h>
#include <string.h>

void enc_lea(unsigned char* c, unsigned char* p, unsigned char* key, unsigned int keyLen);
void dec_lea(unsigned char* p, unsigned char* c, unsigned int* key, unsigned int keyLen);
void round_enc(unsigned int* y, unsigned int* x, unsigned int* rk, unsigned int i);
void round_dec(unsigned int* y, unsigned int* x, unsigned int* rk, unsigned int i);
void enc_key_schedule(unsigned char* k, unsigned int* rk, unsigned int len);
void dec_key_schedule(unsigned char* k, unsigned int* rk, unsigned int len);