#!/bin/sh
set -x
cmake -DCMAKE_BUILD_TYPE=Debug .
make
