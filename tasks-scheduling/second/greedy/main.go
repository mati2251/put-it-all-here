package main

import (
	"fmt"
	"os"
	"sort"
)

type Task struct {
	ID        int
	ReadyTime int
	ExecTime  int
}

type MachineSpeed float32

type Instance struct {
	machines []MachineSpeed
	tasks    []Task
	count    int
}

func fromFile(path string) Instance {
	file, err := os.Open(path)
	if err != nil {
		panic(err)
	}
	defer file.Close()
	var n int
	fmt.Fscanf(file, "%d", &n)
	machines := make([]MachineSpeed, 5)
	fmt.Fscanf(file, "%f %f %f %f %f", &machines[0], &machines[1], &machines[2], &machines[3], &machines[4])
	tasks := make([]Task, n)
	for i := 0; i < n; i++ {
		fmt.Fscanf(file, "%d %d\n", &tasks[i].ExecTime, &tasks[i].ReadyTime)
		tasks[i].ID = i
	}
	return Instance{machines, tasks, n}
}

func greedy(machines []MachineSpeed, tasks []Task) [][]int {
	sort.Slice(tasks, func(i, j int) bool {
		if tasks[i].ReadyTime == tasks[j].ReadyTime {
			return tasks[i].ExecTime < tasks[j].ExecTime
		}
		return tasks[i].ReadyTime > tasks[j].ReadyTime
	})
	solution := make([][]int, len(machines))
	for i := 0; i < len(machines); i++ {
		solution[i] = make([]int, 0)
	}

	for i := 0; i < len(tasks); i++ {
		solution[i%len(machines)] = append(solution[i%len(machines)], tasks[i].ID)
	}
	return solution
}

func goal(instance Instance, solution [][]int) int {
	var max int64 = 0
	for i := 0; i < len(instance.machines); i++ {
		sum := 0
		for j := 0; j < len(solution[i]); j++ {
			if instance.tasks[solution[i][j]].ReadyTime > sum {
				sum += instance.tasks[solution[i][j]].ReadyTime - sum
			}
			sum += instance.tasks[solution[i][j]].ExecTime
		}
		var over float64 = float64(sum) * float64(instance.machines[i])
		if int64(over) > max {
			max = int64(over)
		}
	}
	return int(max)
}

func toFile(instance Instance, solution [][]int, path string) {
	openFile, err := os.Create(path)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	defer openFile.Close()
	openFile.WriteString(fmt.Sprintf("%d\n", goal(instance, solution)))
	for i := 0; i < len(instance.machines); i++ {
		for j := 0; j < len(solution[i]); j++ {
			openFile.WriteString(fmt.Sprintf("%d ", solution[i][j]+1))
		}
		openFile.WriteString("\n")
	}
}

func main() {
	input := os.Args[1]
	output := os.Args[2]
	instance := fromFile(input)
	solution := greedy(instance.machines, instance.tasks)
	toFile(instance, solution, output)
}
