#include "aria.h"
#include "lea.h"
#include "seed.h"
#include "modes_of_operation.h"

void main() {
	byte aria_key[32] = { 0x00 ,0x01 ,0x02 ,0x03 ,0x04 ,0x05 ,0x06 ,0x07 ,
		0x08 ,0x09 ,0x0a ,0x0b ,0x0c ,0x0d ,0x0e ,0x0f ,
		0x10 ,0x11 ,0x12 ,0x13 ,0x14 ,0x15 ,0x16 ,0x17 ,
		0x18 ,0x19 ,0x1a ,0x1b ,0x1c ,0x1d ,0x1e ,0x1f };
	byte aria_p[16] = { 0x00 ,0x11 ,0x22 ,0x33 ,
		0x44 ,0x55 ,0x66 ,0x77 ,
		0x88 ,0x99 ,0xaa ,0xbb ,
		0xcc ,0xdd ,0xee ,0xff };
	byte aria_e[16] = { 0x00, };
	byte aria_m[16] = { 0x00, };

	printf("\n*******************ARIA-128****************************\n");

	printf(" P : ");
	for (int i = 0; i < 16; i++)
		printf("%02x ", aria_p[i]);

	printf("\n");

	aria_enc(aria_p, aria_e, aria_key,16);

	printf(" C : ");
	for (int i = 0; i < 16; i++)
		printf("%02x ", aria_e[i]);

	printf("\n");

	aria_dec(aria_e, aria_m,aria_key, 16);

	printf(" P : ");
	for (int i = 0; i < 16; i++)
		printf("%02x ", aria_m[i]);

	printf("\n*******************ARIA-192****************************\n");

	printf(" P : ");
	for (int i = 0; i < 16; i++)
		printf("%02x ", aria_p[i]);

	printf("\n");

	aria_enc(aria_p, aria_e, aria_key, 24);

	printf(" C : ");
	for (int i = 0; i < 16; i++)
		printf("%02x ", aria_e[i]);

	printf("\n");

	aria_dec(aria_e, aria_m, aria_key, 24);

	printf(" P : ");
	for (int i = 0; i < 16; i++)
		printf("%02x ", aria_m[i]);

	printf("\n*******************ARIA-256****************************\n");

	printf(" P : ");
	for (int i = 0; i < 16; i++)
		printf("%02x ", aria_p[i]);

	aria_enc(aria_p, aria_e, aria_key, 32);

	printf("\n");

	printf(" C : ");
	for (int i = 0; i < 16; i++)
		printf("%02x ", aria_e[i]);

	printf("\n");

	aria_dec(aria_e, aria_m, aria_key, 32);

	printf(" P : ");
	for (int i = 0; i < 16; i++)
		printf("%02x ", aria_m[i]);

	unsigned char lea_k[32] = { 0x0f, 0x1e, 0x2d, 0x3c, 0x4b, 0x5a, 0x69, 0x78, 0x87, 0x96, 0xa5,
	0xb4, 0xc3, 0xd2, 0xe1, 0xf0, 0xf0, 0xe1 , 0xd2 , 0xc3 , 0xb4,  0xa5, 0x96, 0x87, 0x78, 0x69, 0x5a,
	0x4b, 0x3c, 0x2d, 0x1e, 0x0f };
	unsigned char lea_p_128[16] = { 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f };
	unsigned char lea_p_192[16] = { 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f };
	unsigned char lea_p_256[16] = { 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f };
	unsigned char lea_c[16] = { 0x00, };

	printf("\n");

	printf("\n****************LEA-128 TEST****************\n");

	enc_lea(lea_c, lea_p_128, lea_k, 128);

	printf("P : ");
	for (int i = 0; i < 16; i++) printf("%02x ", lea_p_128[i]);
	printf("\n");

	printf("C : ");
	for (int i = 0; i < 16; i++) printf("%02x ", lea_c[i]);
	printf("\n");

	dec_lea(lea_p_128, lea_c, lea_k, 128);
	printf("P : ");
	for (int i = 0; i < 16; i++) printf("%02x ", lea_p_128[i]);

	printf("\n");

	printf("****************LEA-192 TEST****************\n");
	enc_lea(lea_c, lea_p_192, lea_k, 192);

	printf("P : ");
	for (int i = 0; i < 16; i++) printf("%02x ", lea_p_192[i]);
	printf("\n");

	printf("C : ");
	for (int i = 0; i < 16; i++) printf("%02x ", lea_c[i]);
	printf("\n");

	dec_lea(lea_p_192, lea_c, lea_k, 192);
	printf("P : ");
	for (int i = 0; i < 16; i++) printf("%02x ", lea_p_192[i]);
	printf("\n");

	printf("****************LEA-256 TEST****************\n");
	enc_lea(lea_c, lea_p_256, lea_k, 256);

	printf("P : ");
	for (int i = 0; i < 16; i++) printf("%02x ", lea_p_256[i]);
	printf("\n");

	printf("C : ");
	for (int i = 0; i < 16; i++) printf("%02x ", lea_c[i]);
	printf("\n");

	dec_lea(lea_p_256, lea_c, lea_k, 256);
	printf("P : ");
	for (int i = 0; i < 16; i++) printf("%02x ", lea_p_256[i]);
	printf("\n");

	printf("\n*******************SEED-128****************************\n");

	unsigned int pt1[4] = { 0x00010203, 0x04050607,0x08090a0b, 0x0c0d0e0f };

	unsigned int pt2[4] = { 0x00, };

	unsigned int pt3[4] = { 0x83A2F8A2, 0x88641FB9, 0xA4E9A5CC, 0x2F131C7D };

	unsigned int pt4[4] = { 0xB41E6BE2, 0xEBA84A14, 0x8E2EED84, 0x593C5EC7 };


	unsigned int ct1[4] = { 0x00, };
	unsigned int dec[4] = { 0x00, };

	seed_enc(ct1, pt3);

	printf("pt 1 : ");

	for (int i = 0; i < 4; i++) {
		printf("%08x ", pt3[i]);
	}
	printf("\n");

	printf("ct 1 : ");
	for (int i = 0; i < 4; i++) {
		printf("%08x ", ct1[i]);
	}
	printf("\n");

	seed_dec(dec, ct1);

	printf("pt 1 : ");
	for (int i = 0; i < 4; i++) {
		printf("%08x ", dec[i]);
	}
	printf("\n");

}