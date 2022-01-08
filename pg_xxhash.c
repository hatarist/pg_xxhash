#include "postgres.h"
#include <stdio.h>
#include <string.h>
#include "fmgr.h"

#include "libpq/pqformat.h"
#include "utils/builtins.h"

#define XXH_INLINE_ALL
#include "xxhash.h"
#include "xsum_config.h"

#include "pg_xxhash.h"

PG_MODULE_MAGIC;


/* xxhash, 32-bit */

PG_FUNCTION_INFO_V1(pg_xxh32);

Datum pg_xxh32(PG_FUNCTION_ARGS) {
    char *result = malloc(8);

    char *input;
    input = text_to_cstring(PG_GETARG_TEXT_P(0));

    XXH32_hash_t const h = XXH32(input, strlen(input), 0);
    sprintf(result, "%08x", (unsigned)h);

    PG_RETURN_VARCHAR_P(cstring_to_text(result));
}


PG_FUNCTION_INFO_V1(pg_xxh32b);

Datum pg_xxh32b(PG_FUNCTION_ARGS) {
    char *input;
    input = text_to_cstring(PG_GETARG_TEXT_P(0));

    XXH32_hash_t const h = XXH32(input, strlen(input), 0);
    StringInfoData buf;

    pq_begintypsend(&buf);
    pq_sendint32(&buf, (unsigned)h);
    PG_RETURN_BYTEA_P(pq_endtypsend(&buf));
}


/* xxhash, 64-bit */

PG_FUNCTION_INFO_V1(pg_xxh64);

Datum pg_xxh64(PG_FUNCTION_ARGS) {
    char *result = malloc(16);

    char *input;
    input = text_to_cstring(PG_GETARG_TEXT_P(0));

    XXH64_hash_t const h = XXH64(input, strlen(input), 0);
    sprintf(result, "%08x%08x", (unsigned)(h >> 32), (unsigned)h);

    PG_RETURN_VARCHAR_P(cstring_to_text(result));
}


PG_FUNCTION_INFO_V1(pg_xxh64b);

Datum pg_xxh64b(PG_FUNCTION_ARGS) {
    char *input;
    input = text_to_cstring(PG_GETARG_TEXT_P(0));

    XXH64_hash_t const h = XXH64(input, strlen(input), 0);
    StringInfoData buf;

    pq_begintypsend(&buf);
    pq_sendint32(&buf, (unsigned)(h >> 32));
    pq_sendint32(&buf, (unsigned)h);
    PG_RETURN_BYTEA_P(pq_endtypsend(&buf));
}


/* xxhash3, 64-bit */

PG_FUNCTION_INFO_V1(pg_xxh3_64);

Datum pg_xxh3_64(PG_FUNCTION_ARGS) {
    char *result = malloc(16);

    char *input;
    input = text_to_cstring(PG_GETARG_TEXT_P(0));

    XXH64_hash_t const h = XXH3_64bits(input, strlen(input));
    sprintf(result, "%08x%08x", (unsigned)(h >> 32), (unsigned)h);

    PG_RETURN_VARCHAR_P(cstring_to_text(result));
}


PG_FUNCTION_INFO_V1(pg_xxh3_64b);

Datum pg_xxh3_64b(PG_FUNCTION_ARGS) {
    char *input;
    input = text_to_cstring(PG_GETARG_TEXT_P(0));

    XXH64_hash_t const h = XXH3_64bits(input, strlen(input));
    StringInfoData buf;

    pq_begintypsend(&buf);
    pq_sendint32(&buf, (unsigned)(h >> 32));
    pq_sendint32(&buf, (unsigned)h);
    PG_RETURN_BYTEA_P(pq_endtypsend(&buf));
}


/* xxhash3, 128-bit */

PG_FUNCTION_INFO_V1(pg_xxh3_128);

Datum pg_xxh3_128(PG_FUNCTION_ARGS) {
    char *result = malloc(32);

    char *input;
    input = text_to_cstring(PG_GETARG_TEXT_P(0));
    
    XXH128_hash_t const h = XXH3_128bits(input, strlen(input));
    XXH128_canonical_t hcbe128;
    (void)XXH128_canonicalFromHash(&hcbe128, h);
    
    const XSUM_U8* const p = (const XSUM_U8*) &hcbe128;
    sprintf(
        result,
        "%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x%02x",
        p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7], p[8], p[9], p[10], p[11], p[12], p[13], p[14], p[15]
    );
    
    PG_RETURN_VARCHAR_P(cstring_to_text(result));
}


PG_FUNCTION_INFO_V1(pg_xxh3_128b);

Datum pg_xxh3_128b(PG_FUNCTION_ARGS) {
    char *input;
    input = text_to_cstring(PG_GETARG_TEXT_P(0));
    
    XXH128_hash_t const h = XXH3_128bits(input, strlen(input));
    XXH128_canonical_t hcbe128;
    (void)XXH128_canonicalFromHash(&hcbe128, h);
    
    // const XSUM_U32* const p = (const XSUM_U32*) &hcbe128;
    const XSUM_U32* const p = (const XSUM_U32*) &h;
    StringInfoData buf;
    
    pq_begintypsend(&buf);
    pq_sendint32(&buf, (unsigned)p[3]);
    pq_sendint32(&buf, (unsigned)p[2]);
    pq_sendint32(&buf, (unsigned)p[1]);
    pq_sendint32(&buf, (unsigned)p[0]);
    PG_RETURN_BYTEA_P(pq_endtypsend(&buf));
}
