#!/bin/bash
set -e

function compile () {
    meson compile -v -C build
}

function main () {
    compile
}

main
