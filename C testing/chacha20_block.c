// src: https://en.wikipedia.org/wiki/Salsa20#ChaCha_variant 
#include <stdio.h>
#include <stdint.h>
#define ROTL(a,b) (((a) << (b)) | ((a) >> (32 - (b))))
#define QR(a, b, c, d) (             \
	a += b, d ^= a, d = ROTL(d, 16), \
	c += d, b ^= c, b = ROTL(b, 12), \
	a += b, d ^= a, d = ROTL(d,  8), \
	c += d, b ^= c, b = ROTL(b,  7))
#define ROUNDS 20

void chacha_block(uint32_t out[16], uint32_t const in[16])
{
	int i;
	uint32_t x[16];

	for (i = 0; i < 16; ++i)
		x[i] = in[i];
	// 10 loops × 2 rounds/loop = 20 rounds
	for (i = 0; i < ROUNDS; i += 2) {
		// Odd round
		QR(x[0], x[4], x[ 8], x[12]); // column 1
		QR(x[1], x[5], x[ 9], x[13]); // column 2
		QR(x[2], x[6], x[10], x[14]); // column 3
		QR(x[3], x[7], x[11], x[15]); // column 4
		// Even round
		QR(x[0], x[5], x[10], x[15]); // diagonal 1 (main diagonal)
		QR(x[1], x[6], x[11], x[12]); // diagonal 2
		QR(x[2], x[7], x[ 8], x[13]); // diagonal 3
		QR(x[3], x[4], x[ 9], x[14]); // diagonal 4
	}
	for (i = 0; i < 16; ++i)
		out[i] = x[i] + in[i];
}

int main() {
	//input state is composed of all little endian unsigned integers. 
	//1 word = 32 bits


	//constant = 4 words
	//key = 8 words
	//nonce = 3 words
	//counter = 1 word

	//note: I am on a little-endian system. When I write these hex literals, they will be stored into memory in this format. 
	const uint32_t chachaConstant[4] = {
		0x61707865,  // "expa"
		0x3320646e,  // "nd 3"
		0x79622d32,  // "2-by"
		0x6b206574   // "te k"
	};

	uint32_t key[8] = {
		0x03020100,
		0x07060504,
		0x0b0a0908,
		0x0f0e0d0c,
		0x13121110,
		0x17161514,
		0x1b1a1918,
		0x1f1e1d1c
	};

	uint32_t counter[1] = {0x00000001};

	uint32_t nonce[3] = {
		0x09000000,
		0x4a000000,
		0x00000000
	};


	uint32_t initialState[16] = {
    chachaConstant[0], chachaConstant[1], chachaConstant[2], chachaConstant[3],
    key[0], key[1], key[2], key[3], key[4], key[5], key[6], key[7],
    counter[0],
    nonce[0], nonce[1], nonce[2]
	};

	uint32_t out[16];
	chacha_block(out, initialState);

	for(int i = 0; i < 16; i++) {
		printf("%x ", out[i]);
		if ((i + 1) % 4 == 0) printf("\n");
	}
}