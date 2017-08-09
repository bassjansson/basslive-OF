#!/bin/bash

# Go to the directory of this script
cd "${0%/*}"

# Remove the compiled builds
rm -rf ../build/osx/Builds

# Remove the generated api
rm -rf ../docs/api
