#include <stdio.h>
#include <stdlib.h>

#include "bin.h"
#include "mem.h"

void load_bin(char *fpath, mem *mem, unsigned int offset) {
    FILE *fp;
    unsigned int flen;
    unsigned int mlen;
    unsigned int rlen;

    fp = fopen(fpath, "r");

    if (fp == NULL) {
        printf("Unable to load file.\n");
        exit(1);
    }

    fseek(fp, 0L, SEEK_END);
    flen = ftell(fp);
    rewind(fp);

    mlen = mem->size;

    if (flen > mlen) {
        printf("File exceeds the memory capacity.\n%d/%d\n", flen, mlen);
        fclose(fp);
        exit(1);
    }

    rlen = fread(mem->bytes + offset, sizeof(uint8_t), flen, fp);
    printf("Read bin: %d/%d\n", rlen, mlen);

    fclose(fp);
}
