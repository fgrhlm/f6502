#!/bin/bash
set -e

CC65_BIN=$1
SRC=$2
OUT=$3

$CC65_BIN/ca65 $SRC -l $OUT.lst -o $OUT.o
$CC65_BIN/ld65 $OUT.o -o $OUT.bin -m $OUT.map -C ./config
