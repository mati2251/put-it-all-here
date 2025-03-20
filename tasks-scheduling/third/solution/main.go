package main

import (
	"fmt"
	"math"
	"os"
	"slices"
	"strings"
	"time"
)

type Task struct {
	p  []int
	p2  []int
	pt int
	t  []int
	td []int
	d  int
	id int
}

func main() {
	tasks := readInstance(os.Args[1])
    tasksCopy := make([]Task, len(tasks))
    copy(tasksCopy, tasks)
	a, b, c := divideTasks(tasks)
	start := time.Now()
	solution(a, b, c)
	end := time.Now()
	saveSolution(tasks, os.Args[2])
	fmt.Println(end.Sub(start).Milliseconds())
}

func divideTasks(tasks []Task) ([]*Task, []*Task, []*Task) {
	a := make([]*Task, 0)
	b := make([]*Task, 0)
	c := make([]*Task, 0)
	for _, task := range tasks {
		if task.p[0] < task.p[1] && task.p[0] < task.p[2] {
			a = append(a, &task)
		} else if task.p[1] < task.p[0] && task.p[1] < task.p[2] {
			b = append(b, &task)
		} else {
			c = append(c, &task)
		}
	}
	return a, b, c
}

func solution(a []*Task, b []*Task, c []*Task) {
	slices.SortFunc(a, func(a, b *Task) int { return a.d - b.d })
	slices.SortFunc(b, func(a, b *Task) int { return a.d - b.d })
	slices.SortFunc(c, func(a, b *Task) int { return a.d - b.d })
	candidate := [][]*Task{a, b, c}

	waited := [][]*Task{}
	for i := 0; i < 3; i++ {
		waited = append(waited, []*Task{})
	}
	time := []int{0, 0, 0}

	for i := 0; ; i++ {
		if len(candidate[0]) == 0 && len(candidate[1]) == 0 && len(candidate[2]) == 0 && len(waited[0]) == 0 && len(waited[1]) == 0 && len(waited[2]) == 0 {
			break
		}
		currentMachine := i % 3
		var curr *Task
		if len(waited[currentMachine]) == 0 && len(candidate[currentMachine]) == 0 {
			continue
		} else if len(candidate[currentMachine]) == 0 {
			curr = waited[currentMachine][0]
			waited[currentMachine] = waited[currentMachine][1:]
		} else if len(waited[currentMachine]) == 0 {
			curr = candidate[currentMachine][0]
			candidate[currentMachine] = candidate[currentMachine][1:]
		} else if waited[currentMachine][0].d < candidate[currentMachine][0].d {
			curr = waited[currentMachine][0]
			waited[currentMachine] = waited[currentMachine][1:]
		} else {
			curr = candidate[currentMachine][0]
			candidate[currentMachine] = candidate[currentMachine][1:]
		}
		candidateTime := []int{curr.td[0], curr.td[1], curr.td[2], time[currentMachine]}
		newTime := slices.Max(candidateTime)
		curr.t[currentMachine] = newTime
		curr.td[currentMachine] = newTime + curr.p[currentMachine]
		time[currentMachine] = newTime + curr.p[currentMachine]
		curr.p[currentMachine] = math.MaxInt32
		minVal := math.MaxInt32
		minIndex := -1
		for i, p := range curr.p {
			if p < minVal {
				minVal = p
				minIndex = i
			}
		}
		if minVal != math.MaxInt32 && minIndex != -1 {
			waited[minIndex] = append(waited[minIndex], curr)
			slices.SortFunc(waited[minIndex], func(a, b *Task) int {
				return a.d - b.d
			})
		}
	}
}

func saveSolution(tasks []Task, output string) int {
	file, err := os.OpenFile(output, os.O_CREATE|os.O_WRONLY, 0644)
	if err != nil {
		panic(err)
	}
	defer file.Close()
	slices.SortFunc(tasks, func(a, b Task) int { return a.id - b.id })
	goal := 0
	for _, task := range tasks {
		for i := 0; i < 3; i++ {
			goal += int(math.Min(math.Max(float64(task.td[i]-task.d), 0), float64(task.p2[i])))
		}
	}
	fmt.Fprintf(file, "%d\n", goal)
	machine1 := make([]string, len(tasks))
	machine2 := make([]string, len(tasks))
	machine3 := make([]string, len(tasks))
	for i, task := range tasks {
		machine1[i] = fmt.Sprintf("%d", task.t[0])
		machine2[i] = fmt.Sprintf("%d", task.t[1])
		machine3[i] = fmt.Sprintf("%d", task.t[2])
	}
	fmt.Fprintln(file, strings.Join(machine1, " "))
	fmt.Fprintln(file, strings.Join(machine2, " "))
	fmt.Fprintln(file, strings.Join(machine3, " "))
	return goal
}

func readInstance(filename string) []Task {
	file, err := os.Open(filename)
	if err != nil {
		panic(err)
	}
	defer file.Close()

	var n int
	fmt.Fscanf(file, "%d\n", &n)

	tasks := make([]Task, n)
	for i := 0; i < n; i++ {
		tasks[i].p = make([]int, 3)
		tasks[i].p2 = make([]int, 3)
		tasks[i].t = make([]int, 3)
		tasks[i].td = make([]int, 3)
		fmt.Fscanf(file, "%d %d %d %d\n", &tasks[i].p[0], &tasks[i].p[1], &tasks[i].p[2], &tasks[i].d)
        tasks[i].p2[0] = tasks[i].p[0]
        tasks[i].p2[1] = tasks[i].p[1]
        tasks[i].p2[2] = tasks[i].p[2]
		tasks[i].id = i
		for _, p := range tasks[i].p {
			tasks[i].pt += p
		}
	}

	return tasks
}

func saveResult(filename string, totalLateWork int, startTimes [][3]int) {
	file, err := os.Create(filename)
	if err != nil {
		panic(err)
	}
	defer file.Close()

	fmt.Fprintf(file, "%d\n", totalLateWork)
	for j := 0; j < 3; j++ {
		for i := 0; i < len(startTimes); i++ {
			fmt.Fprintf(file, "%d ", startTimes[i][j])
		}
		fmt.Fprintln(file)
	}
}
