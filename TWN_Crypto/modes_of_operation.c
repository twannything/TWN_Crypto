#include "lea.h"
#include "modes_of_operation.h"
#include <stdlib.h>


unsigned int enc_ecb_lea(unsigned char* ct, unsigned char* pt, unsigned int* rk, unsigned int length, unsigned int rem) {

	unsigned char* out;

	out = calloc(16 * (length + 1), sizeof(pt[0]));
	memcpy(out, pt, 16 * length + (rem));
	out[16 * length + rem] = 0x80;
	for (int i = 0; i < 16 * (length + 1); i++) printf("%02x ", out[i]);
	printf("\n");

	unsigned char temp[16] = { 0x00, };
	unsigned char* c_ct = NULL;
	c_ct = calloc((16 * (length + 1)), sizeof(pt[0]));
	for (int i = 0; i < length + 1; i++) {
		//memcpy(temp, pt+(i*16), 16);
		enc_lea(temp, out + (16 * i), rk, 192);
		memcpy(c_ct + (16 * i), temp, 16);
	}
	for (int i = 0; i < 16 * (length + 1); i++) printf("%02x ", c_ct[i]);
	printf("\n");

	memcpy(ct, c_ct, 16 * (length + 1));
	free(out);
	free(c_ct);
	return 0;
}

unsigned int dec_ecb_lea(unsigned char* pt, unsigned char* ct, unsigned int* rk, unsigned int length) {
	unsigned char temp[16] = { 0x00, };

	unsigned char* c_ct = NULL;
	c_ct = calloc(16 * (length + 1), sizeof(pt[0]));

	for (int i = 0; i < length + 1; i++) {
		//memcpy(temp, pt+(i*16), 16);
		dec_lea(temp, ct + (16 * i), rk, 192);
		memcpy(c_ct + (16 * i), temp, 16);
	}

	for (int i = 0; i < 16 * (length + 1); i++) printf("%02x ", c_ct[i]);
	printf("\n");

	memcpy(pt, c_ct, 16 * (length + 1));

	free(c_ct);

}