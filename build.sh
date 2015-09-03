#!/bin/bash
set -euxo pipefail
script_dir=$( cd `dirname $0` && pwd )
cd "$script_dir"
git submodule update
mkdir -p build/googletest
cd build/googletest
cmake ../../googletest
make
