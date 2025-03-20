#!/bin/python
# problem 1 | d_j, S_ij | Y
import sys

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

orders = []
times = []
max_order = task_count
breadth = 7
sorted_tasks = sorted(tasks, key=lambda x: x.d)
for i in range(breadth):
    orders.append([sorted_tasks[i].task_id])

def sort_value(val):
    goal, time = goal_function(tasks, val)
    return (-goal, -time)

for i in range(1, task_count):
    new_orders = []
    for order in orders:
        last_task_id = order[-1]
        s = tasks[last_task_id].s
        sorted_tasks = sorted(tasks, key=lambda x: x.d - s[x.task_id] - x.p)
        new_task_id = None
        for b in range(breadth):
            while new_task_id is None and len(sorted_tasks) > 0:
                for task in sorted_tasks:
                    if task.task_id not in order:
                        new_task_id = task.task_id
                        sorted_tasks.remove(task)
                        break
                    sorted_tasks.remove(task)
            if new_task_id is None:
                break
            new_order = order.copy()
            new_order.append(new_task_id)
            new_orders.append(new_order)
            new_task_id = None
    orders = new_orders
    if len(orders) > max_order:
        orders = sorted(orders, key=sort_value, reverse=True)
        orders = orders[:max_order]
        

orders = sorted(orders, key=sort_value, reverse=True)
# print(goal_function(tasks, orders[0]))
# print(goal_function(tasks, orders[1]))
order = orders[0]
goal, time = goal_function(tasks, order)
# print(sys.argv[1])
print(goal)
# print(time)



