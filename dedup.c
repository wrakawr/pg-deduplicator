#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

typedef int bool;
#define true 1
#define false 0

int main(int argc, char *argv[])
{
       FILE * fp;
       char * line = NULL;
       size_t len = 0;
       ssize_t read;
       bool last_dup = false;

       if (argc < 2) {
         fprintf(stderr, "you should specified the log file path\n");
         exit(EXIT_FAILURE);
       }

       fp = fopen(argv[1], "r");
       if (fp == NULL)
           exit(EXIT_FAILURE);

       while ((read = getline(&line, &len, fp)) != -1) {
           if (strstr(line, "duplicate key") != NULL || strstr(line, "already exists") != NULL) {
             last_dup = true;
             continue;
           }

           if (last_dup && (strstr(line, "STATEMENT") != NULL || strstr(line, "DETAIL") != NULL)) {
             continue;
           }
           
           if (last_dup && line[0] != '<') {
             continue;
           }
           
           last_dup = false;
           printf("%s", line);
       }

       if (line)
           free(line);
       exit(EXIT_SUCCESS);
}
