#!/bin/python3
import os
import subprocess

indexes = ["151764", "151916", "151811", "152089", "151600", "151782", "151839", "151820", "151776", "148130", "151786", "151585" ]

sizes = ["50", "100", "150", "200", "250", "300", "350", "400", "450", "500"]

times = open("times.txt", "w")
solutions = open("solutions.txt", "w")

for i in indexes:
    for size in sizes:
        os.makedirs(f"output/151782/{i}", exist_ok=True)
        p = subprocess.run(["go", "run", "solution/main.go", f"input/{i}/{i}_{size}.in", f"output/151782/{i}/151782_{i}_{size}.out"], capture_output=True)
        print(f"output/151782/{i}/151782_{i}_{size}.out")
        with open(f"output/151782/{i}/151782_{i}_{size}.out") as f:
            solutions.write(f.readline())
        times.write(p.stdout.decode("utf-8"))
        print(p.stdout.decode("utf-8"), end="")

times.close()
solutions.close()

