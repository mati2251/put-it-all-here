package main

import (
	"bufio"
	"fmt"
	"math"
	"os"
	"sort"
	"strconv"
	"strings"
)

type Task struct {
	p  []int
	pt int
	t  []int
	td []int
	d  int
	id int
}

func main() {
    input := os.Args[1]
    output := os.Args[2]
    tasks := readInstance(input)
    file_goal := readSolution(output, tasks)
    if !verifyLegit(tasks) {
        fmt.Println("Bad solution")
        os.Exit(1)
    } 
    if goal(tasks) != file_goal {
        fmt.Println("Bad goal")
        fmt.Println("Expected:", file_goal)
        fmt.Println("Got:", goal(tasks))
        os.Exit(1)
    }
}

func readInstance(filename string) []*Task {
	file, err := os.Open(filename)
	if err != nil {
		panic(err)
	}
	defer file.Close()

	var n int
	fmt.Fscanf(file, "%d\n", &n)

	tasks := make([]*Task, n)
	for i := 0; i < n; i++ {
        tasks[i] = new(Task)
		tasks[i].p = make([]int, 3)
		tasks[i].t = make([]int, 3)
		tasks[i].td = make([]int, 3)
		fmt.Fscanf(file, "%d %d %d %d\n", &tasks[i].p[0], &tasks[i].p[1], &tasks[i].p[2], &tasks[i].d)
		tasks[i].id = i
		for _, p := range tasks[i].p {
			tasks[i].pt += p
		}
	}

	return tasks
}

func readSolution(filename string, tasks []*Task) int {
	goal := 0
	file, err := os.Open(filename)
	if err != nil {
		panic(err)
	}
	defer file.Close()

	fmt.Fscanf(file, "%d\n", &goal)
    reader := bufio.NewReader(file)
	for i := 0; i < 3; i++ {
        current, err := reader.ReadString('\n')
        if err != nil {
            panic(err)
        }
        timesRaw := strings.Split(current[:len(current)-1], " ")
		for j, time := range timesRaw {
			val, err := strconv.Atoi(time)
			if err != nil {
				panic(err)
			}
			tasks[j].t[i] = val
			tasks[j].td[i] = val + tasks[j].p[i]
		}
	}
	return goal
}

func goal(tasks []*Task) int {
	goal := 0
	for _, task := range tasks {
        for i:=0; i<3; i++ {
             goal += int(math.Min(math.Max(float64(task.td[i] - task.d), 0), float64(task.p[i])))
        }
	}
	return goal
}

type Interval struct {
	Start int
	End   int
}

func checkIntervals(starts, ends []int) bool {
	if len(starts) != len(ends) {
		return false
	}

	n := len(starts)
	intervals := make([]Interval, n)

	for i := 0; i < n; i++ {
		intervals[i] = Interval{Start: starts[i], End: ends[i]}
	}

	sort.Slice(intervals, func(i, j int) bool {
		return intervals[i].Start < intervals[j].Start
	})

	for i := 1; i < n; i++ {
		if intervals[i].Start < intervals[i-1].End {
			return false
		}
	}

	return true
}

func verifyLegit(tasks []*Task) bool {
	for _, task := range tasks {
		for i := 0; i < 3; i++ {
            if !checkIntervals(task.t, task.td) {
                return false
            }
		}
	}
	return true
}
