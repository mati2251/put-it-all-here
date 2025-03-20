package main

import (
	"fmt"
	"math"
	"os"
	"sort"
	"strconv"
	"time"

	"golang.org/x/exp/rand"
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

func localGreedy(machines []MachineSpeed, tasks []Task) int64 {
	sort.Slice(tasks, func(i, j int) bool {
		return tasks[i].ExecTime < tasks[j].ExecTime
	})
	var min float64 = math.MaxFloat32
	groupSize := len(tasks) / len(machines)
	for i := len(machines) - 1; i >= 0; i-- {
		groupTask := tasks[i*groupSize : (i+1)*groupSize]
		var sum float64 = 0
		for _, task := range groupTask {
			sum += float64(task.ExecTime)
		}
		sum *= float64(machines[i])
		min = math.Min(min, sum)
	}
	return int64(min)
}

func instanceGenerator(n int) Instance {
	now := uint64(time.Now().UnixNano())
	rand.Seed(now)
	machines := []MachineSpeed{1, 1.2, 1.4, 1.6, 1.8}
	tasks := make([]Task, n)
	for i := 0; i < n; i++ {
		ExecTime := rand.Intn(1000)
		tasks[i] = Task{i, 0, ExecTime}
	}

	sort.Slice(tasks, func(i, j int) bool {
		return tasks[i].ExecTime < tasks[j].ExecTime
	})

	var readyTime int64
	for i := 0; i < n; i += 20 {
		if i+20 > n {
			readyTime += localGreedy(machines, tasks[i:])
		} else {
			readyTime += localGreedy(machines, tasks[i:i+20])
		}
		for j := 0; j < 20 ; j++ {
            if i+j >= n {
                break
            }
			tasks[i+j].ReadyTime = int(readyTime)
		}
	}
	rand.Shuffle(n, func(i, j int) {
		tasks[i], tasks[j] = tasks[j], tasks[i]
	})

	for i := 0; i < n; i++ {
		tasks[i].ID = i
	}

	return Instance{machines, tasks, n}
}

func toFile(instance Instance) {
	openFile, err := os.Create(fmt.Sprintf("151782_%d.in", instance.count))
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	defer openFile.Close()
	openFile.WriteString(fmt.Sprintf("%d\n", instance.count))
	for _, machine := range instance.machines {
		openFile.WriteString(fmt.Sprintf("%f ", machine))
	}
	openFile.WriteString("\n")
	for _, task := range instance.tasks {
		openFile.WriteString(fmt.Sprintf("%d %d\n", task.ExecTime, task.ReadyTime))
	}
	openFile.Close()
}

func main() {
	nRaw := os.Args[1]
	n, err := strconv.Atoi(nRaw)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	instance := instanceGenerator(n)
	toFile(instance)
}
