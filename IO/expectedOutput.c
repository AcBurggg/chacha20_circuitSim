//Source: https://en.wikipedia.org/wiki/Salsa20#ChaCha_variant 
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	const uint32_t chachaConstant[4] = {
		0x61707865,  // "expa"
		0x3320646e,  // "nd 3"
		0x79622d32,  // "2-by"
		0x6b206574   // "te k"
	};

	//chat GPT
	uint32_t key[8], counter[1], nonce[3];

    FILE *inputFile = fopen("inputs.txt", "r");
    if (!inputFile) {
        perror("Failed to open inputs.txt");
        return 1;
    }
    char line[256];
    while (fgets(line, sizeof(line), inputFile)) {
        if (strncmp(line, "key:", 4) == 0) {
            sscanf(line + 4, "%x %x %x %x %x %x %x %x",
                   &key[0], &key[1], &key[2], &key[3],
                   &key[4], &key[5], &key[6], &key[7]);
        } else if (strncmp(line, "counter:", 8) == 0) {
            sscanf(line + 8, "%x", &counter[0]);
        } else if (strncmp(line, "nonce:", 6) == 0) {
            sscanf(line + 6, "%x %x %x", &nonce[0], &nonce[1], &nonce[2]);
        }
    }
    fclose(inputFile);
	//end chatGPT block

	uint32_t initialState[16] = {
    chachaConstant[0], chachaConstant[1], chachaConstant[2], chachaConstant[3],
    key[0], key[1], key[2], key[3], key[4], key[5], key[6], key[7],
    counter[0],
    nonce[0], nonce[1], nonce[2]
	};

	printf("\n");
	printf("====Initial state of matrix====\n");
	for (int i = 0; i < 16; i++) {
		printf("%08x ", initialState[i]);
		if ((i + 1) % 4 == 0) printf("\n");
	}
	printf("\n");
	printf("\n");
	printf("\n");

	uint32_t out[16];
	chacha_block(out, initialState);

	printf("Keystream: \n");
	for (int i = 0; i < 16; i++) {
		printf("%08x \n", out[i]);
	}
	printf("\n");
	printf("\n");
	printf("\n");
    
    //the following section was generated with ChatGPT. It opens the .dat file and creates a uint32_t[16] from it. 
    uint32_t plaintext[16] = {0};
    FILE *fp = fopen("hexoutput.dat", "r");
    if (!fp) {
        perror("Failed to open hexoutput.dat");
        return 1;
    }
    char hexLine[16];
    int i = 0;
    while (fgets(hexLine, sizeof(hexLine), fp) && i < 16) {
        // Remove newline if present
        hexLine[strcspn(hexLine, "\n")] = 0;

        if (strlen(hexLine) == 8) {
            uint32_t value = (uint32_t)strtoul(hexLine, NULL, 16);
            plaintext[i++] = value;
        }
    }
    fclose(fp);
    //ChatGPT generation block ends

	// printf("Plaintext matrix:");
	// for(int i = 0; i < 16; i++) {
	// 	printf("%08x ", plaintext[i]);
	// }
	// printf("\n");



    uint32_t ciphertext[16];
    printf("================The ciphertext to be displayed in circuit sim should be as follows================\n");
    for (int i = 0; i < 16; i++) {
		if (plaintext[i] == 0) {
			ciphertext[i] = 0;
		} else {
        	ciphertext[i] = plaintext[i] ^ out[i];
		}
        printf("%08x\n", ciphertext[i]);
    }

}