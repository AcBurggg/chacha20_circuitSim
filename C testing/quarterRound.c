#include <stdint.h>
#include <stdio.h>

#define ROTL(a,b) (((a) << (b)) | ((a) >> (32 - (b))))

#define QR(a, b, c, d) (             \
	a += b, d ^= a, d = ROTL(d, 16), \
	c += d, b ^= c, b = ROTL(b, 12), \
	a += b, d ^= a, d = ROTL(d,  8), \
	c += d, b ^= c, b = ROTL(b,  7))



void quarterRound(uint32_t a, uint32_t b, uint32_t c, uint32_t d) {
    QR(a, b, c, d);
    printf("a: %x\n", a);
    printf("b: %x\n", b);
    printf("c: %x\n", c);
    printf("d: %x\n", d);
}

void printBinary(uint32_t x) {
    for (int i = 31; i >= 0; i--) {
        printf("%c", (x & (1u << i)) ? '1' : '0');
        if (i % 8 == 0 && i != 0) printf(" "); // Optional spacing every byte
    }
    printf("\n");
}

int main() {
    uint32_t a = 0x23451234;
    uint32_t b = 0x12347654;
    uint32_t c = 0x56431212;
    uint32_t d = 0x77665543; 
    quarterRound(a, b, c, d);


    // //testing rotation subcircuits//
    // uint32_t test = 0x12347654;
    // test = ROTL(test, 16);
    // printf("test rotated 16: %x\n", test);

    // test = 0x12347654;
    // test = ROTL(test, 12);
    // printf("test rotated 12: %x\n", test);

    // test = 0x12347654;
    // test = ROTL(test, 8);
    // printf("test rotated 8: %x\n", test);

    // test = 0x12347654;
    // test = ROTL(test, 7);
    // printf("test rotated 7: %x\n", test);



    return 0; 
}