#!/bin/bash

# Go to the directory of this script
cd "${0%/*}"

# Remove build/bin and docs/api directory
rm -rf ../build/bin
rm -rf ../docs/api
