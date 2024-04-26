#!/bin/bash
set -e

function compile () {
    meson compile -C build
}

function main () {
    compile
}

main
