#!/bin/python

import sys

current_key = None
current_count = 0

for line in sys.stdin:
    line = line.strip()
    key, value = line.split('\t')
    if current_key == key:
        current_count += int(value)
    else:
        if current_key != None:
            print(f"{current_key}\t{current_count}")
        current_key = key
        current_count = int(value)

print(f"{current_key}\t{current_count}")
