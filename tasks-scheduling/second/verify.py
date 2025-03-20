#!/usr/bin/env python3
import os, signal, sys, subprocess

def signal_handler(sig, frame):
    sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)

invalid = open("invalid.txt", "w")

for folder in os.listdir("output"):
    for instance_author in os.listdir(f"output/{folder}"):
        for file in os.listdir(f"output/{folder}/{instance_author}"):
            author = file.split("_")[0]
            instance = file[len(author)+1:].removesuffix(".out")
            process = subprocess.run(["go", "run", "verify/main.go", f"input/{instance_author}/{instance}.in", f"output/{folder}/{instance_author}/{author}_{instance}.out"])
            if process.returncode != 0:
                print(f"\033[91m FAIL: output/{folder}/{instance_author}/{author}_{instance}.out\033[0m")
                invalid.write(f"output/{folder}/{instance_author}/{author}_{instance}.out\n")
            else:
                print(f"\033[92m OK: output/{folder}/{instance_author}/{author}_{instance}.out\033[0m")

invalid.close()
