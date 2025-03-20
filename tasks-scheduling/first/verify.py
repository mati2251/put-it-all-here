import sys

class Task:
    def __init__(self, task_id, task_count):
        self.task_id = task_id
        self.p = 0
        self.s = [0] * task_count
        self.d = 0

file = open(sys.argv[1], "r")
output =  open(sys.argv[2], "r")

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

goal = int(output.readline().strip())
order = list(map(int, output.readline().strip().split(" ")))

if len(order) != task_count:
    print("Invalid order count")
    sys.exit(1)

if len(set(order)) != task_count or min(order) != 1 or max(order) != task_count:
    print("Invalid order values")
    sys.exit(1)

def goal_function(tasks, order, time = 0, s = [0] * task_count):
    sum = 0
    for i in order:
        time += s[i] + tasks[i].p
        s = tasks[i].s
        sum += min(tasks[i].p, max(time - tasks[i].d, 0))
    return sum, time

order = [x - 1 for x in order]

if goal != goal_function(tasks, order)[0]:
    print(goal_function(tasks, order)[0])
    print(goal)
    print("Invalid goal function")
    sys.exit(1)

print("OK")
