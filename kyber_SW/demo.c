#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "kyber/src/kem.h"
#include "kyber/common/randombytes.h"
#include "kyber/common/Funciones_demo.h"
#include "kyber/common/Funciones_test.h"


void main(int argc, char** argv)
{
	int k = 0;
	int e = 0;
	int d = 0;
	int v = 0;

	for (int arg = 1; arg < argc; arg++) {

		if (argv[arg][0] == '-') {
			if (argv[arg][1] == 'h') {
				printf("\n Usage: ./kyber_demo [-h] [-k] [-e] [-d] \n");
				printf("\n -h : Show the help.");
				printf("\n -k : Key Generation");
				printf("\n -e : Encryption");
				printf("\n -d : Decryption");
				printf("\n -v : Verbose level");
				printf("\n \t 1 : Show functions under execution.");
				printf("\n \t 2 : Show intermediate results.");
				printf("\n \t 3 : Show keys.");
				printf("\n \n");

				return;
			}
			else if (argv[arg][1] == 'k') {
				k = 1;
			}
			else if (argv[arg][1] == 'e') {
				e = 1;
			}
			else if (argv[arg][1] == 'd') {
				d = 1;
			}
			else if (argv[arg][1] == 'v') {
				if (arg < argc - 1) v = atoi(argv[arg + 1]);
			}
			else {
				printf("\n Unknow option: %s\n", argv[arg]);
			}
		}
	}


	unsigned char		* ct;
	unsigned char		* ss;
	unsigned char		* ss1;
	unsigned char		* pk;
	unsigned char		* sk;
    //unsigned char       ct[CRYPTO_CIPHERTEXTBYTES], ss[CRYPTO_BYTES], ss1[CRYPTO_BYTES];
    //unsigned char       pk[CRYPTO_PUBLICKEYBYTES], sk[CRYPTO_SECRETKEYBYTES];

	ct		= malloc(sizeof(unsigned char) * CRYPTO_CIPHERTEXTBYTES);
	ss		= malloc(sizeof(unsigned char) * CRYPTO_BYTES);
	ss1		= malloc(sizeof(unsigned char) * CRYPTO_BYTES);

	pk		= malloc(sizeof(unsigned char) * CRYPTO_PUBLICKEYBYTES);
	sk		= malloc(sizeof(unsigned char) * CRYPTO_SECRETKEYBYTES);


	/*
	srand(time(NULL));

    for (int i = 0; i < 48; i++)
        entropy_input[i] = rand()*i;

    randombytes_init(entropy_input, NULL, 256);
	for (int i = 0; i < 100; i++) {
		randombytes(seed, 48);
	}

	randombytes_init(seed, NULL, 256);
	*/

	if (k) {
		gen_files();

		if (v >= 1) printf("\n Generating keys ... ");

		crypto_kem_keypair(pk, sk);

		if(v >= 1) printf("\t Complete ");

		if (v >= 1) printf("\n Storing keys ... ");

		save_keys(pk, sk);

		if (v >= 1) printf("\t Complete ");

		if (v >= 3) {
			printf("\n");
			printf("\x1B[35m"); // magenta
			printf("sk: "); show_array(sk, CRYPTO_SECRETKEYBYTES, 32);
			printf("\x1B[0m");
		}
		if (v >= 3) {
			printf("\n");
			printf("\x1B[36m"); // cyan
			printf("pk: "); show_array(pk, CRYPTO_PUBLICKEYBYTES, 32);
			printf("\x1B[0m");
		}
	}

	if (e) {

		if (v >= 1) printf("\n Loading public key ... ");

		load_pk_key(pk);

		if (v >= 1) printf("\t Complete ");
		if (v >= 3) {
			printf("\n");
			printf("\x1B[36m"); // cyan
			printf("pk: "); show_array(pk, CRYPTO_PUBLICKEYBYTES, 32);
			printf("\x1B[0m");
		}

		if (v >= 1) printf("\n Generating shared secret ... ");

		crypto_kem_enc(ct, ss, pk);

		if (v >= 1) printf("\t Complete ");

		if (v >= 1) printf("\n Storing ciphertext ... ");

		save_ct(ct);

		if (v >= 1) printf("\t Complete ");

		if (v >= 1) {
			printf("\n");
			printf("\x1B[0m"); // white
			printf("ss: %s \n", ss);
			printf("\x1B[0m");
		}
		if (v >= 2) {
			printf("\n");
			printf("\x1B[33m"); // yellow
			printf("ct: "); show_array(ct, CRYPTO_CIPHERTEXTBYTES, 32);
			printf("\x1B[0m");
		}
	}

	if (d) {

		if (v >= 1) printf("\n Loading secret key ... ");

		load_sk_key(sk);
		
		if (v >= 1) printf("\t Complete ");
		if (v >= 1) printf("\n Loading ciphertext ... ");

		load_ct(ct);
		
		if (v >= 1) printf("\t Complete ");
		if (v >= 2) {
			printf("\n");
			printf("\x1B[33m"); // yellow
			printf("ct: "); show_array(ct, CRYPTO_CIPHERTEXTBYTES, 32);
			printf("\x1B[0m");
		}
		if (v >= 3) {
			printf("\n");
			printf("\x1B[35m"); // magenta
			printf("sk: "); show_array(sk, CRYPTO_SECRETKEYBYTES, 32);
			printf("\x1B[0m");
		}

		if (v >= 1) printf("\n Recovering shared secret ... ");

		crypto_kem_dec(ss, ct, sk);
		
		if (v >= 1) printf("\t Complete ");

		if (v >= 1) {
			printf("\n");
			printf("\x1B[0m"); // white
			printf("ss: %s \n", ss);
			printf("\x1B[0m");
		}
	}

	printf("\x1B[0m");
	printf("\n\n");

}

/*
void main()
{
	uint8_t pk[CRYPTO_PUBLICKEYBYTES];
	uint8_t sk[CRYPTO_SECRETKEYBYTES];
	uint8_t ct[CRYPTO_CIPHERTEXTBYTES];
	uint8_t key_a[CRYPTO_BYTES];
	uint8_t key_b[CRYPTO_BYTES];

	//Alice generates a public key
	crypto_kem_keypair(pk, sk);

	//Bob derives a secret key and creates a response
	crypto_kem_enc(ct, key_b, pk);

	//Alice uses Bobs response to get her shared key
	crypto_kem_dec(key_a, ct, sk);

	if (memcmp(key_a, key_b, CRYPTO_BYTES)) {
		printf("ERROR keys\n");	
	}

}
*/