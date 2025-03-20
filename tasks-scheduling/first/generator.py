#!/bin/python
# problem 1 | d_j, S_ij | Y
import numpy as np
import sys
from multiprocessing import Process


class Task:
    def __init__(self, task_id, task_count):
        self.task_id = task_id
        self.p = np.random.randint(1, 10000)
        self.s = np.random.randint(1, 10000, task_count)
        self.d = 0

    def __str__(self) -> str:
        return f"{self.p} {self.d}"

    def s_to_str(self):
        return " ".join(map(str, self.s))
    
    def get_s(self, task_id):
        return self.s[task_id]
            
def greedy_solution(tasks: list[Task], current, time=0):
    s = current.s
    tasks.pop(tasks.index(current))
    if len(tasks) == 0:
        return time
    min_next = min(tasks, key=lambda x: x.p + s[x.task_id])
    min_time = min_next.p + s[min_next.task_id]
    return greedy_solution(tasks, min_next, time + min_time)

solutions = 0
min_value = 100000000000000
last_s = list()

def count_possible_solutions(tasks: list[Task], time, current):
    if time > current.d:
        return
    if len(tasks) == 1: 
        global solutions
        global min_value
        global last_s
        solutions += 1
        if time < min_value:
            min_value = time
            last_s = current.s
        return
    s = current.s
    tasks.pop(tasks.index(current))
    for task in tasks: 
        count_possible_solutions(tasks.copy(), time + s[task.task_id] + task.p, task)

count = int(sys.argv[1])
tasks = np.array([Task(i, count) for i in range(count)])

# array split to parts containing 10 elements
splits = np.array_split(tasks, count // 10)
ls = list()
current_time = 0
for i, split in enumerate(splits):
    min_task = min(split, key=lambda x: x.p)
    greedy = greedy_solution(split.tolist(), min_task, min_task.p)
    for task in split:
        task.d = greedy
    print(f"Split {i} - {greedy}")
    task = Task(0, 0)
    if len(ls) != 0:
        task = min(split, key=lambda x: ls[x.task_id])
        current_time += ls[task.task_id] 
    else:
        task = min(split, key=lambda x: x.p)
    print(task.task_id, end="...")
    p1 = Process(target=count_possible_solutions(split.copy().tolist(), task.p, task), name='Process_inc_forever')
    p1.start()
    p1.join(timeout=60*20)
    if min_value == 100000000000000:
        min_value = greedy
    print()
    current_time += min_value + 1
    for task in split:
        task.d = current_time
    ls = last_s
    print(f"Split {i} - {greedy} - {min_value} - {solutions}")
    print(f"Due time: {current_time}")
    solutions = 0
    min_value = 100000000000000

tasks = np.concatenate(splits)
np.random.shuffle(tasks)

file = open(f"tests/151782_{count}.in", "w+")

file.write(f"{count}\n")
print(len(tasks))
for task in tasks:
    file.write(f"{str(task)}\n")
count = 0
for task in tasks:
    file.write(f"{task.s_to_str()}\n")
    count += 1
print(count)
print(len(tasks))
file.close()
