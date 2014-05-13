### Overview

remove duplicate key errors from postgres log 9.3 files


### Compile
gcc dedup.c -o dedup

### Usage

./dedup /var/lib/pgsql/9.3/data/pg_log/postgresql-Tue.log > postgresql-Tue-deduplicated.log
