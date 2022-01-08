#include "postgres.h"
#include <stdio.h>
#include <string.h>
#include "fmgr.h"

#include "utils/builtins.h"

#define XXH_INLINE_ALL
#include "xxhash.h"
#include "xsum_config.h"

#include "pg_xxhash.h"

PG_MODULE_MAGIC;


PG_FUNCTION_INFO_V1(pg_xxh32);

Datum pg_xxh32(PG_FUNCTION_ARGS) {
    char *result = malloc(8);

    char *input;
    input = text_to_cstring(PG_GETARG_TEXT_P(0));

    XXH32_hash_t const h = XXH32(input, strlen(input), 0);
    sprintf(result, "%08x", (unsigned)h);

    PG_RETURN_VARCHAR_P(cstring_to_text(result));
}


PG_FUNCTION_INFO_V1(pg_xxh64);

Datum pg_xxh64(PG_FUNCTION_ARGS) {
    char *result = malloc(16);

    char *input;
    input = text_to_cstring(PG_GETARG_TEXT_P(0));

    XXH64_hash_t const h = XXH64(input, strlen(input), 0);
    sprintf(result, "%08x%08x", (unsigned)(h >> 32), (unsigned)h);

    PG_RETURN_VARCHAR_P(cstring_to_text(result));
}


PG_FUNCTION_INFO_V1(pg_xxh3_64);

Datum pg_xxh3_64(PG_FUNCTION_ARGS) {
    char *result = malloc(16);

    char *input;
    input = text_to_cstring(PG_GETARG_TEXT_P(0));

    XXH64_hash_t const h = XXH3_64bits(input, strlen(input));
    sprintf(result, "%08x%08x", (unsigned)(h >> 32), (unsigned)h);

    PG_RETURN_VARCHAR_P(cstring_to_text(result));
}


PG_FUNCTION_INFO_V1(pg_xxh3_64_uint);

Datum pg_xxh3_64_uint(PG_FUNCTION_ARGS) {
    char *input;
    input = text_to_cstring(PG_GETARG_TEXT_P(0));

    uint64_t const h = XXH3_64bits(input, strlen(input));
    PG_RETURN_UINT64(h);
}


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