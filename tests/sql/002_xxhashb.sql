-- test with example query
SELECT url, xxh32b(url), xxh64b(url), xxh3_64b(url), xxh128b(url) FROM (SELECT 'https://example.com' AS url) x;