MODULE_big = xxhash
EXTENSION = xxhash
DATA = xxhash--0.0.1.sql

OBJS	= xxhash.o pg_xxhash.o

PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
