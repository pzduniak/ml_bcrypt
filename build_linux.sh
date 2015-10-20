#!/bin/bash

cmake -DCMAKE_C_FLAGS=-m64 -DCMAKE_CXX_FLAGS=-m64 CMakeLists.txt
make
mv libml_bcrypt.so ml_bcrypt_64.so

cmake -DCMAKE_C_FLAGS=-m32 -DCMAKE_CXX_FLAGS=-m32 CMakeLists.txt
make
mv libml_bcrypt.so ml_bcrypt_32.so