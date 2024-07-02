// preload_exec.c
#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef int (*orig_execv_t)(const char *path, char *const argv[]);

int execv(const char *path, char *const argv[]) {
    static orig_execv_t orig_execv = NULL;
    if (!orig_execv) {
        orig_execv = (orig_execv_t)dlsym(RTLD_NEXT, "execv");
    }

    if (strstr(path, "gcc") != NULL) {
        FILE *log = fopen("/tmp/compile.log", "a");
        if (log) {
            fprintf(log, "execv called: %s\n", path);
            for (int i = 0; argv[i] != NULL; i++) {
                fprintf(log, "  arg[%d]: %s\n", i, argv[i]);
            }
            fclose(log);
        }
    }

    return orig_execv(path, argv);
}