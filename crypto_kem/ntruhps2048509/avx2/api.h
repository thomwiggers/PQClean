#ifndef PQCLEAN_NTRUHPS2048509_AVX2_API_H
#define PQCLEAN_NTRUHPS2048509_AVX2_API_H

#define PQCLEAN_NTRUHPS2048509_AVX2_CRYPTO_PUBLICKEYBYTES 699
#define PQCLEAN_NTRUHPS2048509_AVX2_CRYPTO_SECRETKEYBYTES 935
#define PQCLEAN_NTRUHPS2048509_AVX2_CRYPTO_CIPHERTEXTBYTES 699
#define PQCLEAN_NTRUHPS2048509_AVX2_CRYPTO_BYTES 32
#define PQCLEAN_NTRUHPS2048509_AVX2_CRYPTO_ALGNAME "ntruhps2048509"

int PQCLEAN_NTRUHPS2048509_AVX2_crypto_kem_keypair(unsigned char *pk, unsigned char *sk);

int PQCLEAN_NTRUHPS2048509_AVX2_crypto_kem_enc(unsigned char *ct, unsigned char *ss, const unsigned char *pk);

int PQCLEAN_NTRUHPS2048509_AVX2_crypto_kem_dec(unsigned char *ss, const unsigned char *ct, const unsigned char *sk);


#endif
