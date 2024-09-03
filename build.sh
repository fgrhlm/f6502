#!/bin/bash
set -e

function main () {
    local BUILD_DIR="./build"
    
    if [ ! -d $BUILD_DIR ]; then
        meson setup $BUILD_DIR
    fi

    meson compile -v -C $BUILD_DIR
}

main
