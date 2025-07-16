-- test with example query
SELECT url, xxh32(url), xxh64(url), xxh3_64(url), xxh128(url) FROM (SELECT 'https://example.com' AS url) x;