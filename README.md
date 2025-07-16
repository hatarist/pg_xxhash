# pg_xxhash

PostgreSQL ❤️ [xxhash](https://github.com/Cyan4973/xxHash)

Tested with xxhash 0.8.1 and PostgreSQL 14.1 on Linux and macOS.

Think twice before even considering to use it in any serious environment.

Issues are discouraged, pull requests are greatly appreciated.


## TODO

 - [ ] seed/secret support


## Build

Make sure you've got the PostgreSQL source code somewhere.  
For Ubuntu/pgdg and PostgreSQL 14: `apt install postgresql-server-dev-14`

    $ make
    $ make install


Enable the extension:

    =# CREATE EXTENSION xxhash;


## Usage

    =# SELECT url, xxh32(url), xxh64(url), xxh3_64(url), xxh128(url) FROM (SELECT 'https://example.com' AS url) x;
    ┌─[ RECORD 1 ]───────────────────────────────┐
    │ url     │ https://example.com              │
    │ xxh32   │ ba15a4a8                         │
    │ xxh64   │ b131752760b48654                 │
    │ xxh3_64 │ 9398cc7c078760e6                 │
    │ xxh128  │ 4879d6aa9d88e9c7a169c008892d4829 │
    └─────────┴──────────────────────────────────┘


    =# SELECT url, xxh32b(url), xxh64b(url), xxh3_64b(url), xxh128b(url) FROM (SELECT 'https://example.com' AS url) x;
    ┌─[ RECORD 1 ]──────────────────────────────────┐
    │ url      │ https://example.com                │
    │ xxh32b   │ \xba15a4a8                         │
    │ xxh64b   │ \xb131752760b48654                 │
    │ xxh3_64b │ \x9398cc7c078760e6                 │
    │ xxh128b  │ \x4879d6aa9d88e9c7a169c008892d4829 │
    └──────────┴────────────────────────────────────┘
