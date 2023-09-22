#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "kem.h"
#include "randombytes.h"
#include "Funciones_demo.h"


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
				printf("\n \t 1 : Muestra las funciones ejecutandose");
				printf("\n \t 2 : Muestra los resultados intermedios");
				printf("\n \t 3 : Muestra las claves");
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
		if (v >= 1) printf("\n Generando claves ... ");

		crypto_kem_keypair(pk, sk);

		if(v >= 1) printf("\t Completado ");

		if (v >= 1) printf("\n Almacenando claves ... ");

		save_keys(pk, sk);

		if (v >= 1) printf("\t Completado ");

		if (v >= 3) {
			printf("\n sk: "); for (int i = 0; i < CRYPTO_SECRETKEYBYTES; i++) printf("%02x", sk[i]);
		}
		if (v >= 3) {
			printf("\n pk: "); for (int i = 0; i < CRYPTO_PUBLICKEYBYTES; i++) printf("%02x", pk[i]);
		}
	}

	if (e) {

		if (v >= 1) printf("\n Cargando clave publica ... ");

		load_pk_key(pk);

		if (v >= 1) printf("\t Completado ");
		if (v >= 3) {
			printf("\n pk: "); for (int i = 0; i < CRYPTO_PUBLICKEYBYTES; i++) printf("%02x", pk[i]);
		}

		if (v >= 1) printf("\n Generando clave compartida ... ");

		crypto_kem_enc(ct, ss, pk);

		if (v >= 1) printf("\t Completado ");

		if (v >= 1) printf("\n Almacenando ciphertext ... ");

		save_ct(ct);

		if (v >= 1) printf("\t Completado ");

		if (v >= 1) {
			printf("\n ss: "); for (int i = 0; i < CRYPTO_BYTES; i++) printf("%02x", ss[i]);
		}
		if (v >= 2) {
			printf("\n ct: "); for (int i = 0; i < CRYPTO_CIPHERTEXTBYTES; i++) printf("%02x", ct[i]);
		}
	}

	if (d) {

		if (v >= 1) printf("\n Cargando clave privada ... ");

		load_sk_key(sk);
		
		if (v >= 1) printf("\t Completado ");
		if (v >= 1) printf("\n Cargando ciphertext ... ");

		load_ct(ct);
		
		if (v >= 1) printf("\t Completado ");
		if (v >= 2) {
			printf("\n ct: "); for (int i = 0; i < CRYPTO_CIPHERTEXTBYTES; i++) printf("%02x", ct[i]);
		}
		if (v >= 3) {
			printf("\n sk: "); for (int i = 0; i < CRYPTO_SECRETKEYBYTES; i++) printf("%02x", sk[i]);
		}

		if (v >= 1) printf("\n Recuperando clave compartida ... ");

		crypto_kem_dec(ss1, ct, sk);
		
		if (v >= 1) printf("\t Completado ");

		if (v >= 1) {
			printf("\n ss: "); for (int i = 0; i < CRYPTO_BYTES; i++) printf("%02x", ss1[i]);
		}
	}

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