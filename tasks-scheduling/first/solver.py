#!/bin/python
# problem 1 | d_j, S_ij | Y
import sys
import numpy as np
import statistics
import datetime

class Task:
    def __init__(self, task_id, task_count):
        self.task_id = task_id
        self.p = 0
        self.s = [0] * task_count
        self.d = 0

file = open(sys.argv[1], "r")
output =  open(sys.argv[2], "w")

task_id = 0
task_count = int(file.readline())

tasks = []
for i in range(task_count):
    task = Task(task_id, task_count)
    line = file.readline().split(" ")
    task.p = int(line[0])
    task.d = int(line[1])
    tasks.append(task)
    task_id += 1
for i in range(task_count):
    line = file.readline().strip().split(" ")
    s = list(map(int, line))
    tasks[i].s = s

def goal_function(tasks, order, time = 0, s = [0] * task_count):
    sum = 0
    for i in order:
        time += s[i] + tasks[i].p
        s = tasks[i].s
        sum += min(tasks[i].p, max(time - tasks[i].d, 0))
    return sum, time

mean = statistics.mean([x.p for x in tasks])

def evaluate(task, s, time):
    val = task.d - time - task.p - s[task.task_id]
    if val < -mean/2:
        return 99999999999
    return val

def greedy_solution(tasks, s: list[int]):
    # vec_p = np.array([x.p for x in tasks])
    # vec_d = np.array([x.d for x in tasks])
    # mat_s = np.array([x.s for x in tasks])
    tasks = tasks.copy()
    time = 0
    order = []
    while len(tasks) > 0:
        min_index = np.argmin([ evaluate(x, s, time) for x in tasks])
        min_next = tasks[min_index]
        time += min_next.p + s[min_next.task_id]
        order.append(min_next.task_id)
        tasks = np.delete(tasks, min_index)
        s = min_next.s
    return order, time

orginals = tasks.copy()

greeedy_order, time = greedy_solution(tasks, [0] * task_count)
tasks = sorted(tasks, key=lambda x: (x.d, -x.p))
time = 0
last_s = [0] * task_count

group_size = 6

def optimal_solution(tasks, order, s: list[int] = [0] * task_count, time = 0):
    if len(tasks) == 0:
        global orginals
        goal, new_time = goal_function(orginals, order, time)
        return goal, order, new_time
    max_goal = 99999999999
    max_order = []
    max_time = 99999999999
    for i in range(len(tasks)):
        new_task = tasks[i]
        new_tasks = tasks[:i] + tasks[i+1:]
        new_order = order + [new_task.task_id]
        new_goal, new_order, new_time = optimal_solution(new_tasks, new_order, s, time)
        if new_goal < max_goal:
            max_goal = new_goal
            max_order = new_order
            max_time = new_time
        elif new_goal == max_goal:
            if new_time < max_time:
                max_goal = new_goal
                max_order = new_order
                max_time = new_time
    return max_goal, max_order, max_time

# time start count
time_start = datetime.datetime.now()
last_s = [0] * task_count
time = 0
order = []
greeedy_order = greedy_solution(orginals, [0] * task_count)
tasks = [orginals[i] for i in greeedy_order[0]]

while len(tasks) > 0:
    count = group_size
    if len(tasks) < group_size:
        count = len(tasks)
    group = tasks[:count]
    goal, new_order, time = optimal_solution(group, [], last_s, time)
    last_s = orginals[new_order[-1]].s
    order += new_order
    tasks = tasks[count:]

time_end = datetime.datetime.now()
time_star = time_start.timestamp() * 1000
time_end = time_end.timestamp() * 1000
print(f"Exec time {time_end - time_star}")
goal, time = goal_function(orginals, order)
print(f"Goal {goal}")
print(f"Time {time}")
output.write(f"{goal}\n")
order_str = " ".join(map(lambda x: str(x+1), order))
output.write(f"{order_str}\n")
output.close()

