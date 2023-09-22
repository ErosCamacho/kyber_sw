CC ?= /usr/bin/cc
#CFLAGS += -Wall -Wextra -Wpedantic -Wmissing-prototypes -Wredundant-decls \
  -Wshadow -Wpointer-arith -O3 -fomit-frame-pointer
#NISTFLAGS += -Wno-unused-result -O3 -fomit-frame-pointer
RM = /bin/rm

SOURCES = kex.c kem.c indcpa.c polyvec.c poly.c ntt.c cbd.c reduce.c verify.c Funciones_demo.c
SOURCESKECCAK = $(SOURCES) fips202.c symmetric-shake.c
SOURCESNINETIES = $(SOURCES) sha256.c sha512.c aes256ctr.c symmetric-aes.c
HEADERS = params.h kex.h kem.h indcpa.h polyvec.h poly.h ntt.h cbd.h reduce.c verify.h symmetric.h Funciones_demo.h
HEADERSKECCAK = $(HEADERS) fips202.h
HEADERSNINETIES = $(HEADERS) aes256ctr.h sha2.h

.PHONY: all shared

#all: demo_kem512

all: \
  demo_kem512 \
  demo_kem768 \
  demo_kem1024 \
  demo_kem512-90s \
  demo_kem768-90s \
  demo_kem1024-90s 

shared: \
  libpqcrystals_kyber512_ref.so \
  libpqcrystals_kyber768_ref.so \
  libpqcrystals_kyber1024_ref.so \
  libpqcrystals_kyber512-90s_ref.so \
  libpqcrystals_kyber768-90s_ref.so \
  libpqcrystals_kyber1024-90s_ref.so \
  libpqcrystals_fips202_ref.so \
  libpqcrystals_aes256ctr_ref.so \
  libpqcrystals_sha2_ref.so

libpqcrystals_fips202_ref.so: fips202.c fips202.h
	$(CC) -shared -fPIC $(CFLAGS) fips202.c -o libpqcrystals_fips202_ref.so

libpqcrystals_aes256ctr_ref.so: aes256ctr.c aes256ctr.h
	$(CC) -shared -fPIC $(CFLAGS) aes256ctr.c -o libpqcrystals_aes256ctr_ref.so

libpqcrystals_sha2_ref.so: sha256.c sha512.c sha2.h
	$(CC) -shared -fPIC $(CFLAGS) sha256.c sha512.c -o libpqcrystals_sha2_ref.so

libpqcrystals_kyber512_ref.so: $(SOURCES) $(HEADERS) symmetric-shake.c
	$(CC) -shared -fPIC $(CFLAGS) -DKYBER_K=2 $(SOURCES) symmetric-shake.c -o libpqcrystals_kyber512_ref.so

libpqcrystals_kyber768_ref.so: $(SOURCES) $(HEADERS) symmetric-shake.c
	$(CC) -shared -fPIC $(CFLAGS) -DKYBER_K=3 $(SOURCES) symmetric-shake.c -o libpqcrystals_kyber768_ref.so

libpqcrystals_kyber1024_ref.so: $(SOURCES) $(HEADERS) symmetric-shake.c
	$(CC) -shared -fPIC $(CFLAGS) -DKYBER_K=4 $(SOURCES) symmetric-shake.c -o libpqcrystals_kyber1024_ref.so

libpqcrystals_kyber512-90s_ref.so: $(SOURCES) $(HEADERS) symmetric-aes.c
	$(CC) -shared -fPIC $(CFLAGS) -DKYBER_K=2 -D KYBER_90S $(SOURCES) symmetric-aes.c -o libpqcrystals_kyber512-90s_ref.so

libpqcrystals_kyber768-90s_ref.so: $(SOURCES) $(HEADERS) symmetric-aes.c
	$(CC) -shared -fPIC $(CFLAGS) -DKYBER_K=3 -D KYBER_90S $(SOURCES) symmetric-aes.c -o libpqcrystals_kyber768-90s_ref.so

libpqcrystals_kyber1024-90s_ref.so: $(SOURCES) $(HEADERS) symmetric-aes.c
	$(CC) -shared -fPIC $(CFLAGS) -DKYBER_K=4 -D KYBER_90S $(SOURCES) symmetric-aes.c -o libpqcrystals_kyber1024-90s_ref.so


demo_kem512: $(SOURCESKECCAK) $(HEADERSKECCAK) demo.c randombytes.c
	$(CC) $(CFLAGS) -DKYBER_K=2 $(SOURCESKECCAK) randombytes.c demo.c -o demo_kyber512

demo_kem768: $(SOURCESKECCAK) $(HEADERSKECCAK) demo.c randombytes.c
	$(CC) $(CFLAGS) -DKYBER_K=3 $(SOURCESKECCAK) randombytes.c demo.c -o demo_kyber768

demo_kem1024: $(SOURCESKECCAK) $(HEADERSKECCAK) demo.c randombytes.c
	$(CC) $(CFLAGS) -DKYBER_K=4 $(SOURCESKECCAK) randombytes.c demo.c -o demo_kyber1024

demo_kem512-90s: $(SOURCESNINETIES) $(HEADERSNINETIES) demo.c randombytes.c
	$(CC) $(CFLAGS) -DKYBER_K=2 -D KYBER_90S $(SOURCESNINETIES) randombytes.c demo.c -o demo_kyber512-90s

demo_kem768-90s: $(SOURCESNINETIES) $(HEADERSNINETIES) demo.c randombytes.c
	$(CC) $(CFLAGS) -DKYBER_K=3 -D KYBER_90S $(SOURCESNINETIES) randombytes.c demo.c -o demo_kyber768-90s

demo_kem1024-90s: $(SOURCESNINETIES) $(HEADERSNINETIES) demo.c randombytes.c
	$(CC) $(CFLAGS) -DKYBER_K=4 -D KYBER_90S $(SOURCESNINETIES) randombytes.c demo.c -o demo_kyber1024-90s

clean:
	-$(RM) -rf *.gcno *.gcda *.lcov *.o *.so
	-$(RM) -rf demo_kem512
	-$(RM) -rf demo_kem768
	-$(RM) -rf demo_kem1024
	-$(RM) -rf demo_kem512-90s
	-$(RM) -rf demo_kem768-90s
	-$(RM) -rf demo_kem1024-90s
