#include <stdlib.h>
#include <stdio.h>

#include "mem.h"

void load_bin(char* fpath, mem* mem, unsigned int offset){
    FILE* fp;
    unsigned int flen;
    unsigned int mlen;

    fp = fopen(fpath, "r");

    if(fp == NULL) { 
        printf("Unable to load file.\n");
        exit(1);
    }

    fseek(fp, 0L, SEEK_END);
    flen = ftell(fp);
    rewind(fp);
  
    mlen = mem->size;

    if(flen > mlen){
        printf("File exceeds the memory capacity.\n");
        exit(1);
    }

    fread(mem->bytes+=offset, sizeof(uint8_t), mlen, fp); 

    fclose(fp);
}
