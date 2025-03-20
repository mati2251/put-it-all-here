import numpy as np
import sys

class Task:
    def __init__(self, p, d, task_count, task_id):
        self.p = p
        self.s = []
        self.d = d
        self.task_id = task_id
            
def greedy_solution(tasks: list[Task], current, time=0):
    s = current.s
    tasks.pop(tasks.index(current))
    if len(tasks) == 0:
        return time
    min_next = min(tasks, key=lambda x: x.p + s[x.task_id])
    min_time = min_next.p + s[min_next.task_id]
    return greedy_solution(tasks, min_next, time + min_time)

file = open(sys.argv[1], "r")
n = int(file.readline())
tasks = []
for i in range(n):
    line = file.readline().split(" ")
    p = line[0]
    d = line[1]
    tasks.append(Task(p, d, n, i))

for i in range(n):
    line = file.readline().strip().split(" ")
    # remove empty strings
    s = list(map(int, line))
    tasks[i].s = s

task_min_p = min(tasks, key=lambda x: x.p)
result = greedy_solution(tasks.copy(), task_min_p)
print(result)
