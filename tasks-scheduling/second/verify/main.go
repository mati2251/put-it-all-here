package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"strings"
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
	fmt.Fscanf(file, "%d\n", &n)
	machines := make([]MachineSpeed, 5)
	fmt.Fscanf(file, "%f %f %f %f %f\n", &machines[0], &machines[1], &machines[2], &machines[3], &machines[4])
	tasks := make([]Task, n)
	for i := 0; i < n; i++ {
		fmt.Fscanf(file, "%d %d\n", &tasks[i].ExecTime, &tasks[i].ReadyTime)
		tasks[i].ID = i
	}
	return Instance{machines, tasks, n}
}

func goal(instance Instance, solution [][]int) float32 {
	var max float32 = 0
    var sum float32 = 0
	for i := 0; i < len(instance.machines); i++ {
		sum = 0
		for j := 0; j < len(solution[i]); j++ {
			if float32(instance.tasks[solution[i][j]].ReadyTime) > sum {
				sum = float32(instance.tasks[solution[i][j]].ReadyTime)
			}
			sum += (float32(instance.tasks[solution[i][j]].ExecTime) * float32(instance.machines[i]))
		}
		if sum > max {
			max = sum
		}
	}
	return max
}

func solutionFromFile(path string) (int, [][]int) {
	file, err := os.Open(path)
	if err != nil {
		panic(err)
	}
	defer file.Close()
	var solution [][]int = make([][]int, 0)
	var goal float32
	fmt.Fscanf(file, "%f\n", &goal)
	var line string
    reader := bufio.NewReader(file)
	for i := 0; ; i++ {
        line, err = reader.ReadString('\n') 
        line = strings.TrimSuffix(line, "\n")
        if err != nil {
            break
        }
        solution = append(solution, make([]int, 0))
		splits := strings.Split(line, " ")
        if len(splits) == 1 && splits[0] == "" {
            continue
        }
		for j := 0; j < len(splits); j++ {
			var task int
			fmt.Sscanf(splits[j], "%d", &task)
            if task == -1 {
                continue
            }
			solution[i] = append(solution[i], task - 1)
		}
	}
	return int(goal), solution
}

func main() {
	input := os.Args[1]
	output := os.Args[2]
	instance := fromFile(input)
	solutionGoal, solution := solutionFromFile(output)
	expectedGoal := goal(instance, solution)
	if solutionGoal != int(math.Round(float64(expectedGoal))){
		fmt.Println("Expected goal is ", expectedGoal, " but got ", solutionGoal)
        os.Exit(1)
	} else {
        fmt.Println("Solution is correct")
        os.Exit(0)
    }
}
