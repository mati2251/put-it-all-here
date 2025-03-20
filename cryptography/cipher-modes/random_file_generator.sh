#!/bin/bash
head -c 1MB </dev/urandom > random_file_1MB.txt
head -c 10MB </dev/urandom > random_file_10MB.txt
head -c 100MB </dev/urandom > random_file_100MB.txt
head -c 1GB </dev/urandom > random_file_1GB.txt
