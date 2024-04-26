#!/bin/bash

set -e

# https://github.com/amb5l/6502_65C02_functional_tests/
# https://github.com/cc65/cc65

TESTS_DIR="/home/rcd/proj/6502_65C02_functional_tests/ca65"

CC65_DIR="/home/rcd/proj/cc65/bin"
CA65=$CC65_DIR/ca65
LD65=$CC65_DIR/ld65

BIN_DIR="./tests/6502_bin"

function make_func_test () {
    local TEST_NAME="func_test"
    local TEST_SRC=$TESTS_DIR/6502_functional_test.ca65
    local TEST_CFG=$TESTS_DIR/example.cfg
    local TEST_OBJ=$BIN_DIR/$TEST_NAME.o
    local TEST_BIN=$BIN_DIR/$TEST_NAME.bin
    local TEST_LST=$BIN_DIR/$TEST_NAME.lst

    echo "building ${TEST_NAME} (${TEST_SRC})"
    $CA65 $TEST_SRC -o $TEST_OBJ -l $TEST_LST
    $LD65 $TEST_OBJ -o $TEST_BIN -C $TEST_CFG
}

function main () {
    if [ ! -d $BIN_DIR ]; then
        mkdir $BIN_DIR
    fi

    make_func_test 
}

main
