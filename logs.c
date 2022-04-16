#include "logs.h"

#include <assert.h>
#include <stdio.h>

void log(int code, char * msg) {
    printf("\n(!) %s\n", msg);
    getchar();
    exit(code);
}
