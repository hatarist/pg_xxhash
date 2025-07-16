MODULE_big = xxhash
EXTENSION = xxhash
DATA = xxhash--0.0.1.sql xxhash--0.0.2.sql xxhash--0.0.1--0.0.2.sql

TESTS = $(wildcard test/sql/*.sql)
REGRESS = $(patsubst test/sql/%.sql,%,$(TESTS))
REGRESS_OPTS = --inputdir=test

OBJS	= xxhash.o pg_xxhash.o

PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
