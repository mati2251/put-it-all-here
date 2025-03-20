package main

import (
	"fmt"
	"math/rand"
	"os"
	"strconv"
)

func main() {
    n, _ := strconv.Atoi(os.Args[1])
	const pMin, pMax = 5, 2000
	const tightness = 3
	const maxDeadlineOffset = 10

	file, err := os.Create(fmt.Sprintf("input/151782/151782_%d.in", n))
	if err != nil {
		fmt.Println("Error: ", err)
		return
	}
	defer file.Close()

	fmt.Fprintf(file, "%d\n", n)

	for i := 0; i < n; i++ {
		p1 := rand.Intn(pMax-pMin+1) + pMin
		p2 := rand.Intn(pMax-pMin+1) + pMin
		p3 := rand.Intn(pMax-pMin+1) + pMin

		totalTime := p1 + p2 + p3

		d := totalTime/tightness + rand.Intn(maxDeadlineOffset)

		fmt.Fprintf(file, "%d %d %d %d\n", p1, p2, p3, d)
	}

    fmt.Println(file.Name())
}
