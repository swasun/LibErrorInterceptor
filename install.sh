#!/bin/bash

cd $PWD/build/release
cmake --build . --config Release --target install
