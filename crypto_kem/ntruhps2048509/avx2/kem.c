#include "randombytes.h"
#include "api.h"
#include "crypto_hash_sha3256.h"
#include "params.h"
#include "verify.h"
#include "sample.h"
#include "owcpa.h"

// API FUNCTIONS 
int PQCLEAN_NTRUHPS2048509_AVX2_crypto_kem_keypair(unsigned char *pk, unsigned char *sk)
{
  unsigned char seed[NTRU_SAMPLE_FG_BYTES];

  randombytes(seed, NTRU_SAMPLE_FG_BYTES);
  PQCLEAN_NTRUHPS2048509_AVX2_owcpa_keypair(pk, sk, seed);

  randombytes(sk+NTRU_OWCPA_SECRETKEYBYTES, NTRU_PRFKEYBYTES);

  return 0;
}

int PQCLEAN_NTRUHPS2048509_AVX2_crypto_kem_enc(unsigned char *c, unsigned char *k, const unsigned char *pk)
{
  poly r, m;
  unsigned char rm[NTRU_OWCPA_MSGBYTES];
  unsigned char rm_seed[NTRU_SAMPLE_RM_BYTES];

  randombytes(rm_seed, NTRU_SAMPLE_RM_BYTES);

  PQCLEAN_NTRUHPS2048509_AVX2_sample_rm(&r, &m, rm_seed);

  PQCLEAN_NTRUHPS2048509_AVX2_poly_S3_tobytes(rm, &r);
  PQCLEAN_NTRUHPS2048509_AVX2_poly_S3_tobytes(rm+NTRU_PACK_TRINARY_BYTES, &m);
  crypto_hash_sha3256(k, rm, NTRU_OWCPA_MSGBYTES);

  PQCLEAN_NTRUHPS2048509_AVX2_poly_Z3_to_Zq(&r);
  PQCLEAN_NTRUHPS2048509_AVX2_owcpa_enc(c, &r, &m, pk);

  return 0;
}

int PQCLEAN_NTRUHPS2048509_AVX2_crypto_kem_dec(unsigned char *k, const unsigned char *c, const unsigned char *sk)
{
  int i, fail;
  unsigned char rm[NTRU_OWCPA_MSGBYTES];
  unsigned char buf[NTRU_PRFKEYBYTES+NTRU_CIPHERTEXTBYTES];

  fail = 0;

  /* Check that unused bits of last byte of ciphertext are zero */
  fail |= c[NTRU_CIPHERTEXTBYTES-1] & (0xff << (8 - (7 & (NTRU_LOGQ*NTRU_PACK_DEG))));

  fail |= PQCLEAN_NTRUHPS2048509_AVX2_owcpa_dec(rm, c, sk);
  /* If fail = 0 then c = Enc(h, rm). There is no need to re-encapsulate. */
  /* See comment in PQCLEAN_NTRUHPS2048509_AVX2_owcpa_dec for details.                                */

  crypto_hash_sha3256(k, rm, NTRU_OWCPA_MSGBYTES);

  /* shake(secret PRF key || input ciphertext) */
  for(i=0;i<NTRU_PRFKEYBYTES;i++)
    buf[i] = sk[i+NTRU_OWCPA_SECRETKEYBYTES];
  for(i=0;i<NTRU_CIPHERTEXTBYTES;i++)
    buf[NTRU_PRFKEYBYTES + i] = c[i];
  crypto_hash_sha3256(rm, buf, NTRU_PRFKEYBYTES+NTRU_CIPHERTEXTBYTES);

  PQCLEAN_NTRUHPS2048509_AVX2_cmov(k, rm, NTRU_SHAREDKEYBYTES, fail);

  return 0;
}