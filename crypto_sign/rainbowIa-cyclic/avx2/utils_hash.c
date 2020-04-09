/// @file utils_hash.c
/// @brief the adapter for SHA2 families in openssl.
///
///

#include "utils_hash.h"

#include "sha2.h"

#define _HASH_LEN 32

static inline
int _hash( unsigned char *digest, const unsigned char *m, unsigned long long mlen ) {
    sha256(digest, m, mlen);
    return 0;
}





static inline
int expand_hash( unsigned char *digest, unsigned n_digest, const unsigned char *hash ) {
    if ( _HASH_LEN >= n_digest ) {
        for (unsigned i = 0; i < n_digest; i++) {
            digest[i] = hash[i];
        }
        return 0;
    } else {
        for (unsigned i = 0; i < _HASH_LEN; i++) {
            digest[i] = hash[i];
        }
        n_digest -= _HASH_LEN;
    }

    while ( _HASH_LEN <= n_digest ) {
        _hash( digest + _HASH_LEN, digest, _HASH_LEN );

        n_digest -= _HASH_LEN;
        digest += _HASH_LEN;
    }
    unsigned char temp[_HASH_LEN];
    if ( n_digest ) {
        _hash( temp, digest, _HASH_LEN );
        for (unsigned i = 0; i < n_digest; i++) {
            digest[_HASH_LEN + i] = temp[i];
        }
    }
    return 0;
}




int hash_msg( unsigned char *digest, unsigned len_digest, const unsigned char *m, unsigned long long mlen ) {
    unsigned char buf[_HASH_LEN];
    _hash( buf, m, mlen );

    return expand_hash( digest, len_digest, buf );
}


