#include "lea.h"
#include "aria.h"
#include "seed.h"
#include "modes_of_operation.h"
#include <stdlib.h>


unsigned int mo_block_cipher(unsigned char* ct, unsigned char* pt, unsigned char* key, unsigned int keyLen, unsigned int length, unsigned int rem, unsigned int alg, unsigned int mode) {

	unsigned char* out;

	out = calloc(16 * (length + 1), sizeof(pt[0]));
	memcpy(out, pt, 16 * length + (rem));
	out[16 * length + rem] = 0x80;
	for (int i = 0; i < 16 * (length + 1); i++) printf("%02x ", out[i]);
	printf("\n");
	//out : padding message

	unsigned char temp[16] = { 0x00, };
	unsigned char* c_ct = NULL;
	c_ct = calloc((16 * (length + 1)), sizeof(pt[0]));
	if (mode == ECB) {
		if (alg == LEA) {

			unsigned int lea_rk[192] = { 0x00, };
			enc_key_schedule(key, lea_rk, keyLen);
			for (int i = 0; i < length + 1; i++) {
				//memcpy(temp, pt+(i*16), 16);
				enc_lea(temp, out + (16 * i), lea_rk, keyLen);
				memcpy(c_ct + (16 * i), temp, 16);
			}
			for (int i = 0; i < 16 * (length + 1); i++) printf("%02x ", c_ct[i]);
			printf("\n");

			memcpy(ct, c_ct, 16 * (length + 1));
			free(out);
			free(c_ct);
		}
		else if (alg == ARIA) {
			byte aria_w[16 * (12 + 1)] = { 0x00 };
			Key_expansion(aria_w, key, keyLen);
			for (int i = 0; i < length + 1; i++) {
				//memcpy(temp, pt+(i*16), 16);
				aria_enc(temp, out + (16 * i), aria_w, keyLen);
				memcpy(c_ct + (16 * i), temp, 16);
			}
			for (int i = 0; i < 16 * (length + 1); i++) printf("%02x ", c_ct[i]);
			printf("\n");

			memcpy(ct, c_ct, 16 * (length + 1));
			free(out);
			free(c_ct);
		}
		else if (alg == SEED) {
			for (int i = 0; i < length + 1; i++) {
				//memcpy(temp, pt+(i*16), 16);
				seed_enc(out + (16 * i),temp);
				memcpy(c_ct + (16 * i), temp, 16);
			}
			for (int i = 0; i < 16 * (length + 1); i++) printf("%02x ", c_ct[i]);
			printf("\n");

			memcpy(ct, c_ct, 16 * (length + 1));
			free(out);
			free(c_ct);
		}
	}
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

