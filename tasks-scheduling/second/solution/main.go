package main

import (
	"fmt"
	"math"
	"os"
	"slices"
	"sort"
	"time"
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

func toFile(solution [][]int, goal int, path string) {
	openFile, err := os.Create(path)
	if err != nil {
		fmt.Println(err)
		os.Exit(1)
	}
	defer openFile.Close()
	openFile.WriteString(fmt.Sprintf("%d\n", goal))
	for i := 0; i < len(solution); i++ {
		for j := 0; j < len(solution[i]); j++ {
			openFile.WriteString(fmt.Sprintf("%d", solution[i][j]+1))
			if j != len(solution[i])-1 {
				openFile.WriteString(" ")
			}
		}
		openFile.WriteString("\n")
	}
}

func solution(instance Instance) (float64, [][]int) {
	n := len(instance.tasks) + 1
	m := len(instance.machines)
	r := m * m
	table := make([][][]float64, n)

	for i := 0; i < n; i++ {
		table[i] = make([][]float64, r)
		for j := 0; j < r; j++ {
			table[i][j] = make([]float64, m)
		}
	}

	sortedTasks := make([]Task, n-1)
	copy(sortedTasks, instance.tasks)

	sort.Slice(sortedTasks, func(i, j int) bool {
		if sortedTasks[i].ReadyTime == sortedTasks[j].ReadyTime {
			return sortedTasks[i].ExecTime > sortedTasks[j].ExecTime
		}
		return sortedTasks[i].ReadyTime < sortedTasks[j].ReadyTime
	})

	last := make([][]float64, m)
	for i := 1; i < n; i++ {
		last = table[i-1]
		for j := 0; j < r; j++ {
			table[i][j] = fill(sortedTasks[i-1], instance.machines[j%m], last, j%m, m, r, int(j/m))
		}
	}

	// for i := 0; i < n; i++ {
	//     fmt.Println("i = ", i)
	//     for j := 0; j < r; j++ {
	//         fmt.Println(table[i][j])
	//     }
	// }

	var min float64 = float64(1<<63 - 1)
	best := 0
	for i := 0; i < m; i++ {
		localMin := slices.Max(table[n-1][i])
		if localMin < min {
			min = localMin
			best = i
		}
	}

	solution := make([][]int, m)
	solution[best] = []int{sortedTasks[n-2].ID}

	for i := n - 1; i > 1; i-- {
		current := table[i][best]
		for j := 0; j < r; j++ {
			last := table[i-1][j]
			copyLast := make([]float64, m)
			copy(copyLast, last)
			if copyLast[best%m] < float64(sortedTasks[i-1].ReadyTime) {
				copyLast[best%m] = float64(sortedTasks[i-1].ReadyTime)
			}
			copyLast[best%m] = copyLast[best%m] + float64(sortedTasks[i-1].ExecTime)*float64(instance.machines[best%m])
			if slices.Equal(copyLast, current) {
				best = j
				solution[j%m] = append(solution[j%m], sortedTasks[i-2].ID)
				break
			}
		}
	}

	for i := 0; i < m; i++ {
		slices.Reverse(solution[i])
	}
	return min, solution
}

func fill(task Task, machine MachineSpeed, last [][]float64, j int, m int, r int, which int) []float64 {
	newLast := make([][]float64, r)
	for i := 0; i < r; i++ {
		newLast[i] = make([]float64, m)
		copy(newLast[i], last[i])
	}
	for k := 0; k < r; k++ {
		if newLast[k][j] < float64(task.ReadyTime) {
			newLast[k][j] = float64(task.ReadyTime)
		}
		newLast[k][j] += float64(task.ExecTime) * float64(machine)
	}

	sort.Slice(newLast, func(i, j int) bool {
        // max1 := slices.Max(newLast[i])
        // max2 := slices.Max(newLast[j])
        // if max1 == max2 {
        //     avg := 0.0
        //     avg2 := 0.0
        //     for k := 0; k < m; k++ {
        //         avg += newLast[i][k]
        //         avg2 += newLast[j][k]
        //     }
        //     avg /= float64(m)
        //     avg2 /= float64(m)
        //     over1 := 0
        //     over2 := 0
        //     for k := 0; k < m; k++ {
        //         over1 += int(math.Abs(float64(newLast[i][k]) - avg))
        //         over2 += int(math.Abs(float64(newLast[j][k]) - avg2))
        //     }
        //     return over1 > over2
        // }
		return slices.Max(newLast[i]) < slices.Max(newLast[j])
	})
    //
    // lastEle := newLast[len(newLast)-1]
    //
    // for i := len(newLast)-2; i > 0; i-- {
    //    if slices.Equal(newLast[i], lastEle) {
    //         newLast = append(newLast[:i], newLast[i+1:]...)
    //         if len(newLast) < 6 {
    //             break
    //         }
    //     }
    //     lastEle = newLast[i]
    // }
    //
	return newLast[which]
}

func main() {
	input := os.Args[1]
	output := os.Args[2]
	instance := fromFile(input)
	start := time.Now()
	goal, solution := solution(instance)
	end := time.Now()
	fmt.Println(end.Sub(start).Milliseconds())
	toFile(solution, int(math.Round(goal)), output)
}
