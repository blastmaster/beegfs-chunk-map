#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <limits.h>

#include <leveldb/c.h>

int main(int argc, char **argv)
{
    if (argc != 2) {
        fputs("usage: bp-cm-query <map-folder>\n", stderr);
        return 1;
    }

    leveldb_options_t *db_options = leveldb_options_create();
    leveldb_readoptions_t *read_options = leveldb_readoptions_create();
    char *errmsg = NULL;
    leveldb_t *db = leveldb_open(db_options, argv[1], &errmsg);
    if (errmsg != NULL) {
        fprintf(stderr, "leveldb error: %s\n", errmsg);
        return 1;
    }
    leveldb_free(errmsg);

    char chunk_name[200];
    while (fgets(chunk_name, sizeof(chunk_name), stdin))
    {
        size_t chunk_name_len = strlen(chunk_name) - 1;
        chunk_name[chunk_name_len] = '\0';
        size_t filename_len;
        char *filename = leveldb_get(
                db,
                read_options,
                chunk_name, chunk_name_len,
                &filename_len,
                &errmsg);
        leveldb_free(errmsg);
        char filename0[PATH_MAX];
        char filename_fixed[PATH_MAX];
        if (filename == NULL) {
	  fprintf(stderr, "Unknown %s\n", chunk_name);
	} else {
	  snprintf(filename0, sizeof(filename0), "%.*s", (int)filename_len, filename);
	  printf("%s\n", filename0);
	}
    }
}
