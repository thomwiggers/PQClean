#include <stdint.h>
#include "crypto_sort_int32.h"
#include "djbsort/int32_sort.h"

// The avx2 version of djbsort (version 20180729) is used for sorting.
// The source can be found at https://sorting.cr.yp.to/
void PQCLEAN_NTRUHPS2048509_AVX2_crypto_sort_int32(void *array,long long n)
{
  int32_sort(array, n);
}
