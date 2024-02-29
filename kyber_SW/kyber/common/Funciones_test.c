#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "../src/poly.h"
#include "../src/params.h"

void show_array(const unsigned char *r, const unsigned int size, const unsigned int mod) {

	int ind = 0;

	printf("\n");
	for (int i = 0; i < (int)ceil((double)size / (double)mod); i++) {
		for (int j = 0; j < mod; j++) {
			ind = i * mod + j;
			if (ind < size) printf("%02x", r[ind]);
			else printf("  ");
		}
		printf("\n");
	}
}

void show_poly(const poly *r, const unsigned int mod) {
	int ind = 0;

	printf("\n");
	for (int i = 0; i < (int)ceil((double)KYBER_N / (double)mod); i++) {
		for (int j = 0; j < mod; j++) {
			ind = i * mod + j;
			if (ind < KYBER_N) printf("%03d: %04d \t", ind, r->coeffs[ind]);
			else printf("        \t");
		}
		printf("\n");
	}

}