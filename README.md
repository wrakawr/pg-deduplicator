### Overview

remove duplicate key errors from postgres log 9.3 files


### Compile
gcc dedup.c -o dedup

### Usage

./dedup /var/lib/pgsql/9.3/data/pg_log/postgresql-Tue.log > postgresql-Tue-deduplicated.log

### Cronjob example

    0 1 * * * /bin/bash /opt/maintain.sh

and the maintain.sh

    #!/bin/bash

    logdir="/var/lib/pgsql/9.3/data/pg_log/"

    yd=$(date --date="1 day ago" +"%a")
    /opt/pg-deduplicator/dedup ${logdir}postgresql-$yd.log > ${logdir}/postgresql-$yd-deduplicated.log
    rm -f {$logdir}/postgresql-$yd.log
