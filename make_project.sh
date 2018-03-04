#!/bin/bash
echo "begin rm -rf CMakeCache.txt CMakeFiles/"
rm -rf CMakeCache.txt CMakeFiles/

echo "begin cmake ./"
cmake ./

echo "begin make"
make -j4
