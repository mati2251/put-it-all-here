#!/bin/python
import subprocess

n = [50, 100, 150, 200, 250, 300, 350, 400, 450, 500]

for i in n:
    p = subprocess.run(["go", "run", "generator/main.go", f"{i}"])
