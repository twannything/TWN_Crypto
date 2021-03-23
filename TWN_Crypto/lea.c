#pragma once
#include "lea.h"

#define ROR(x,i) (((x)>>(i)) | ((x)<<(32-(i))))
#define ROL(x,i) (((x)<<(i)) | ((x)>>(32-(i))))


unsigned int delta[8] = { 0xc3efe9db, 0x44626b02, 0x79e27c8a, 0x78df30ec, 0x715ea49e, 0xc785da0a, 0xe04ef22a, 0xe5c40957 };

void enc_lea(unsigned char* c, unsigned char* p, unsigned int* rk, unsigned int len) {
	unsigned int x[4] = { NULL };
	unsigned int tmp[4] = { NULL };
	int nr = 0;
	if (len == 128)
		nr = 24;
	else if (len == 192)
		nr = 28;
	else if (len == 256)
		nr = 32;
	else {
		printf("wrong key length !!!\n");
		return;
	}

	memcpy(x, p, 16);
	for (int i = 0; i < nr; i++) {
		round_enc(tmp, x, rk + (6 * i), i);
		memcpy(x, tmp, 16);
	}
	memcpy(c, x, 16);
}

void dec_lea(unsigned char* p, unsigned char* c, unsigned int* rk, unsigned int len) {
	unsigned int x[4] = { NULL };
	unsigned int tmp[4] = { NULL };
	int nr = 0;

	if (len == 128)
		nr = 24;
	else if (len == 192)
		nr = 28;
	else if (len == 256)
		nr = 32;
	else {
		printf("wrong key length !!!\n");
		return;
	}

	memcpy(x, c, 16);
	for (int i = 0; i < nr; i++) {
		round_dec(tmp, x, rk + (6 * (nr - 1)) - (6 * i), i);
		memcpy(x, tmp, 16);
	}
	memcpy(p, x, 16);
}


void round_enc(unsigned int* y, unsigned int* x, unsigned int* rk, unsigned int i) {
	*(y) = ROL(((*x) ^ (*rk)) + (*(x + 1) ^ *(rk + 1)), 9);
	*(y + 1) = ROR((*(x + 1) ^ *(rk + 2)) + ((*(x + 2) ^ *(rk + 3))), 5);
	*(y + 2) = ROR((*(x + 2) ^ *(rk + 4)) + ((*(x + 3) ^ *(rk + 5))), 3);
	*(y + 3) = *x;
}

void round_dec(unsigned int* y, unsigned int* x, unsigned int* rk, unsigned int i) {

	*(y) = *(x + 3);
	*(y + 1) = (ROR(*x, 9) - (*(y) ^ *rk)) ^ *(rk + 1);
	*(y + 2) = (ROL(*(x + 1), 5) - (*(y + 1) ^ *(rk + 2))) ^ *(rk + 3);
	*(y + 3) = (ROL(*(x + 2), 3) - (*(y + 2) ^ *(rk + 4))) ^ *(rk + 5);
}


void enc_key_schedule(unsigned char* k, unsigned int* rk, unsigned int len) {
	if (len == 128) {
		unsigned int T[4] = { 0x00, };

		memcpy(T, k, 16);
		for (int i = 0; i < 24; i++) {
			T[0] = ROL((T[0] + ROL(delta[i % 4], i)), 1);
			T[1] = ROL((T[1] + ROL(delta[i % 4], i + 1)), 3);
			T[2] = ROL((T[2] + ROL(delta[i % 4], i + 2)), 6);
			T[3] = ROL((T[3] + ROL(delta[i % 4], i + 3)), 11);
			*(rk + (i * 6) + 0) = T[0];
			*(rk + (i * 6) + 1) = T[1];
			*(rk + (i * 6) + 2) = T[2];
			*(rk + (i * 6) + 3) = T[1];
			*(rk + (i * 6) + 4) = T[3];
			*(rk + (i * 6) + 5) = T[1];
		}
	}
	else if (len == 192) {
		unsigned int T[6] = { 0x00, };
		memcpy(T, k, 24);
		for (unsigned int i = 0; i < 28; i++) {
			T[0] = ROL((T[0] + ROL(delta[i % 6], i)), 1);
			T[1] = ROL((T[1] + ROL(delta[i % 6], i + 1)), 3);
			T[2] = ROL((T[2] + ROL(delta[i % 6], i + 2)), 6);
			T[3] = ROL((T[3] + ROL(delta[i % 6], i + 3)), 11);
			T[4] = ROL((T[4] + ROL(delta[i % 6], i + 4)), 13);
			T[5] = ROL((T[5] + ROL(delta[i % 6], i + 5)), 17);
			*(rk + (i * 6) + 0) = T[0];
			*(rk + (i * 6) + 1) = T[1];
			*(rk + (i * 6) + 2) = T[2];
			*(rk + (i * 6) + 3) = T[3];
			*(rk + (i * 6) + 4) = T[4];
			*(rk + (i * 6) + 5) = T[5];
		}
	}
	else if (len == 256) {
		unsigned int T[8] = { 0x00, };
		memcpy(T, k, 32);
		for (int i = 0; i < 32; i++) {

			T[((6 * i)) % 8] = ROL((T[((6 * i)) % 8] + ROL(delta[i % 8], i)), 1);
			T[((6 * i) + 1) % 8] = ROL((T[((6 * i) + 1) % 8] + ROL(delta[i % 8], i + 1)), 3);
			T[((6 * i) + 2) % 8] = ROL((T[((6 * i) + 2) % 8] + ROL(delta[i % 8], i + 2)), 6);
			T[((6 * i) + 3) % 8] = ROL((T[((6 * i) + 3) % 8] + ROL(delta[i % 8], i + 3)), 11);
			T[((6 * i) + 4) % 8] = ROL((T[((6 * i) + 4) % 8] + ROL(delta[i % 8], i + 4)), 13);
			T[((6 * i) + 5) % 8] = ROL((T[((6 * i) + 5) % 8] + ROL(delta[i % 8], i + 5)), 17);
			*(rk + (i * 6) + 0) = T[((6 * i)) % 8];
			*(rk + (i * 6) + 1) = T[((6 * i) + 1) % 8];
			*(rk + (i * 6) + 2) = T[((6 * i) + 2) % 8];
			*(rk + (i * 6) + 3) = T[((6 * i) + 3) % 8];
			*(rk + (i * 6) + 4) = T[((6 * i) + 4) % 8];
			*(rk + (i * 6) + 5) = T[((6 * i) + 5) % 8];
		}
	}
	else printf("wrong key length!!!\n");
}

void dec_key_schedule(unsigned char* k, unsigned int* rk, unsigned int len) {
	if (len == 128) {
		unsigned int T[4] = { 0x00 };
		memcpy(T, k, 16);
		for (int i = 0; i < 24; i++) {
			T[0] = ROL(T[0] + ROL(delta[i % 4], i), 1);
			T[1] = ROL(T[1] + ROL(delta[i % 4], i + 1), 3);
			T[2] = ROL(T[2] + ROL(delta[i % 4], i + 2), 6);
			T[3] = ROL(T[3] + ROL(delta[i % 4], i + 3), 11);
			*(rk + (23 * 6) - (i * 6) + 0) = T[0];
			*(rk + (23 * 6) - (i * 6) + 1) = T[1];
			*(rk + (23 * 6) - (i * 6) + 2) = T[2];
			*(rk + (23 * 6) - (i * 6) + 3) = T[1];
			*(rk + (23 * 6) - (i * 6) + 4) = T[3];
			*(rk + (23 * 6) - (i * 6) + 5) = T[1];
		}
	}
	else if (len == 192) {
		unsigned int T[6] = { 0x00 };
		memcpy(T, k, 24);
		for (int i = 0; i < 28; i++) {
			T[0] = ROL((T[0] + ROL(delta[i % 6], i)), 1);
			T[1] = ROL((T[1] + ROL(delta[i % 6], i + 1)), 3);
			T[2] = ROL((T[2] + ROL(delta[i % 6], i + 2)), 6);
			T[3] = ROL((T[3] + ROL(delta[i % 6], i + 3)), 11);
			T[4] = ROL((T[4] + ROL(delta[i % 6], i + 4)), 13);
			T[5] = ROL((T[5] + ROL(delta[i % 6], i + 5)), 17);
			*(rk + (27 * 6) - (i * 6) + 0) = T[0];
			*(rk + (27 * 6) - (i * 6) + 1) = T[1];
			*(rk + (27 * 6) - (i * 6) + 2) = T[2];
			*(rk + (27 * 6) - (i * 6) + 3) = T[3];
			*(rk + (27 * 6) - (i * 6) + 4) = T[4];
			*(rk + (27 * 6) - (i * 6) + 5) = T[5];
		}
	}
	else if (len == 256) {
		unsigned int T[8] = { 0x00, };
		memcpy(T, k, 32);
		for (int i = 0; i < 32; i++) {

			T[((6 * i)) % 8] = ROL((T[((6 * i)) % 8] + ROL(delta[i % 8], i)), 1);
			T[((6 * i) + 1) % 8] = ROL((T[((6 * i) + 1) % 8] + ROL(delta[i % 8], i + 1)), 3);
			T[((6 * i) + 2) % 8] = ROL((T[((6 * i) + 2) % 8] + ROL(delta[i % 8], i + 2)), 6);
			T[((6 * i) + 3) % 8] = ROL((T[((6 * i) + 3) % 8] + ROL(delta[i % 8], i + 3)), 11);
			T[((6 * i) + 4) % 8] = ROL((T[((6 * i) + 4) % 8] + ROL(delta[i % 8], i + 4)), 13);
			T[((6 * i) + 5) % 8] = ROL((T[((6 * i) + 5) % 8] + ROL(delta[i % 8], i + 5)), 17);
			*(rk + (31 * 6) - (i * 6) + 0) = T[((6 * i)) % 8];
			*(rk + (31 * 6) - (i * 6) + 1) = T[((6 * i) + 1) % 8];
			*(rk + (31 * 6) - (i * 6) + 2) = T[((6 * i) + 2) % 8];
			*(rk + (31 * 6) - (i * 6) + 3) = T[((6 * i) + 3) % 8];
			*(rk + (31 * 6) - (i * 6) + 4) = T[((6 * i) + 4) % 8];
			*(rk + (31 * 6) - (i * 6) + 5) = T[((6 * i) + 5) % 8];
		}
	}
	else printf("wrong key length!!!\n");
}



