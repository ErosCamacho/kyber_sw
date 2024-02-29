CC ?= /usr/bin/cc
#CFLAGS += -Wall -Wextra -Wpedantic -Wmissing-prototypes -Wredundant-decls \
  -Wshadow -Wpointer-arith -O3 -fomit-frame-pointer
#NISTFLAGS += -Wno-unused-result -O3 -fomit-frame-pointer
RM = /bin/rm

LFLAGS = -lm

PATH_SRC = kyber/src
PATH_CMN = kyber/common
SOURCES = $(PATH_SRC)/kex.c $(PATH_SRC)/kem.c $(PATH_SRC)/indcpa.c $(PATH_SRC)/polyvec.c $(PATH_SRC)/poly.c $(PATH_SRC)/ntt.c $(PATH_SRC)/cbd.c $(PATH_SRC)/reduce.c \
			$(PATH_SRC)/verify.c $(PATH_CMN)/Funciones_demo.c $(PATH_CMN)/Funciones_test.c $(PATH_CMN)/randombytes.c
SOURCESKECCAK = $(SOURCES) $(PATH_SRC)/fips202.c $(PATH_SRC)/symmetric-shake.c
SOURCESNINETIES = $(SOURCES) $(PATH_SRC)/sha256.c $(PATH_SRC)/sha512.c $(PATH_SRC)/aes256ctr.c $(PATH_SRC)/symmetric-aes.c
HEADERS = $(PATH_SRC)/params.h $(PATH_SRC)/kex.h $(PATH_SRC)/kem.h $(PATH_SRC)/indcpa.h $(PATH_SRC)/polyvec.h $(PATH_SRC)/poly.h $(PATH_SRC)/ntt.h $(PATH_SRC)/cbd.h $(PATH_SRC)/reduce.c \
			$(PATH_SRC)/verify.h $(PATH_SRC)/symmetric.h $(PATH_CMN)/Funciones_demo.h $(PATH_CMN)/Funciones_test.h $(PATH_CMN)/randombytes.h
HEADERSKECCAK = $(HEADERS) $(PATH_SRC)/fips202.h
HEADERSNINETIES = $(HEADERS) $(PATH_SRC)/aes256ctr.h $(PATH_SRC)/sha2.h

.PHONY: all

#all: test_kem512

#all: demo_kem512

all: \
  demo_kem512 \
  demo_kem768 \
  demo_kem1024 \
  demo_kem512-90s \
  demo_kem768-90s \
  demo_kem1024-90s 


demo_kem512: $(SOURCESKECCAK) $(HEADERSKECCAK) demo.c 
	$(CC) $(CFLAGS) -DKYBER_K=2 $(SOURCESKECCAK) demo.c -o demo_kyber512 $(LFLAGS)

demo_kem768: $(SOURCESKECCAK) $(HEADERSKECCAK) demo.c 
	$(CC) $(CFLAGS) -DKYBER_K=3 $(SOURCESKECCAK) demo.c -o demo_kyber768 $(LFLAGS)

demo_kem1024: $(SOURCESKECCAK) $(HEADERSKECCAK) demo.c
	$(CC) $(CFLAGS) -DKYBER_K=4 $(SOURCESKECCAK) demo.c -o demo_kyber1024 $(LFLAGS)

demo_kem512-90s: $(SOURCESNINETIES) $(HEADERSNINETIES) demo.c
	$(CC) $(CFLAGS) -DKYBER_K=2 -D KYBER_90S $(SOURCESNINETIES) demo.c -o demo_kyber512-90s $(LFLAGS)

demo_kem768-90s: $(SOURCESNINETIES) $(HEADERSNINETIES) demo.c
	$(CC) $(CFLAGS) -DKYBER_K=3 -D KYBER_90S $(SOURCESNINETIES) demo.c -o demo_kyber768-90s $(LFLAGS)

demo_kem1024-90s: $(SOURCESNINETIES) $(HEADERSNINETIES) demo.c
	$(CC) $(CFLAGS) -DKYBER_K=4 -D KYBER_90S $(SOURCESNINETIES) demo.c -o demo_kyber1024-90s $(LFLAGS)


clean:
	-$(RM) -rf *.gcno *.gcda *.lcov *.o *.so
	-$(RM) -rf demo_kem512
	-$(RM) -rf demo_kem768
	-$(RM) -rf demo_kem1024
	-$(RM) -rf demo_kem512-90s
	-$(RM) -rf demo_kem768-90s
	-$(RM) -rf demo_kem1024-90s
	-$(RM) -rf test_kem512
