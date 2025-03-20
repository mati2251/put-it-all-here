#!/bin/bash
cd declarations
make
cd ..
cd definitions 
make
cd ..
./declarations/declarations.out < $1 > $2.h
./definitions/definitions.out < $1 > $2.cpp