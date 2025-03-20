package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
)

var wordSize int

type node struct {
	value  string
	next   []*node
	prev   []*node
	used   bool
	merged bool
	count  int
}

func readLines(filename string) ([]string, error) {
	file, err := os.Open(filename)
	if err != nil {
		return nil, err
	}
	defer file.Close()
	var lines []string
	scanner := bufio.NewScanner(file)
	for scanner.Scan() {
		lines = append(lines, scanner.Text())
	}
	wordSize = len(lines[0])
	return lines, nil
}

func nodes(lines []string) []*node {
	prevMap := make(map[string][]*node)
	nextMap := make(map[string][]*node)
	nodes := []*node{}
	for _, line := range lines {
		new_node := &node{value: line, used: false, merged: false, count: 1}
		nodes = append(nodes, new_node)
		if _, ok := prevMap[line[1:]]; !ok {
			prevMap[line[1:]] = []*node{}
		}
		if _, ok := nextMap[line[:len(line)-1]]; !ok {
			nextMap[line[:len(line)-1]] = []*node{}
		}
		prevMap[line[1:]] = append(prevMap[line[1:]], new_node)
		nextMap[line[:len(line)-1]] = append(nextMap[line[:len(line)-1]], new_node)
	}
	for _, n := range nodes {
		n.next = nextMap[n.value[1:]]
		n.prev = prevMap[n.value[:len(n.value)-1]]
	}
	return nodes
}

func merge(a *node, offset int) {
	if len(a.prev) == 1 {
		if len(a.prev[0].next) == 1 {
			merge(a.prev[0], offset)
			return
		}
	}
	if len(a.next) == 1 {
		if len(a.next[0].prev) == 1 {
			next := a.next[0]
			a.value = a.value + next.value[wordSize-1-offset:]
			a.next = next.next
			next.used = true
			a.count += next.count
			merge(a, offset)
			return
		}
	}
	if len(a.next) > 0 {
		for _, n := range a.next {
			for i, p := range n.prev {
				if p.value[:wordSize-offset] == a.value[len(a.value)-wordSize+offset:] {
					n.prev[i] = a
				}
			}
		}
	}
	a.merged = true
}

func mergeAll(nodes []*node, new_nodes []*node, offset int) []*node {
	if len(nodes) == 0 {
		return new_nodes
	}
	if nodes[0].merged {
		new_nodes = append(new_nodes, nodes[0])
		nodes = nodes[1:]
		return mergeAll(nodes, new_nodes, offset)
	}
	if nodes[0].used {
		nodes = nodes[1:]
		return mergeAll(nodes, new_nodes, offset)
	}
	merge(nodes[0], offset)
	return mergeAll(nodes, new_nodes, offset)
}

func resetUsed(nodes []*node) {
	for _, n := range nodes {
		n.used = false
		n.merged = false
	}
}

func getStarted(nodes []*node) []*node {
	started := []*node{}
	for _, n := range nodes {
		if len(n.prev) == 0 {
			started = append(started, n)
		}
	}
	if len(started) == 0 && len(nodes) > 0 {
    for _, n := range nodes {
      if len(n.next) != 0 {
        started = append(started, n)
      }
    }
	}
	return started
}

type solution struct {
	value string
	count int
}

func getSolutions(n *node, curr solution) []solution {
	solutions := []solution{}
	n.used = true
	if len(n.next) == 0 {
		n.used = false
		return append(solutions, curr)
	}
	for _, next := range n.next {
		if next.used {
			solutions = append(solutions, curr)
		} else {
			for i := wordSize - 1; i > 0; i-- {
				if n.value[len(n.value)-i:] == next.value[:i] {
					new_curr := solution{curr.value + next.value[i:], curr.count + next.count}
					solutions = append(solutions, getSolutions(next, new_curr)...)
				}
			}
		}
	}
	n.used = false
	return solutions
}

func incresaOffset(nodes []*node, offset int) {
	if offset == 0 {
		return
	}
	prevMap := make(map[string][]*node)
	nextMap := make(map[string][]*node)
	for _, n := range nodes {
		size := len(n.value)
		end := n.value[size-wordSize+offset+1:]
		begin := n.value[:wordSize-1-offset]
		if _, ok := prevMap[end]; !ok {
			prevMap[end] = []*node{}
		}
		if _, ok := nextMap[begin]; !ok {
			nextMap[begin] = []*node{}
		}
		prevMap[end] = append(prevMap[end], n)
		nextMap[begin] = append(nextMap[begin], n)
	}
	for _, n := range nodes {
		size := len(n.value)
		nexts := nextMap[n.value[size-wordSize+offset+1:]]
		prevs := prevMap[n.value[:wordSize-1-offset]]
		for _, next := range nexts {
			add := true
			for _, presentNext := range n.next {
				if presentNext.value == next.value {
					add = false
				}
			}
			if n.value == next.value {
				add = false
			}
			if add {
				n.next = append(n.next, next)
			}
		}
		for _, prev := range prevs {
			add := true
			for _, presentPrev := range n.prev {
				if presentPrev.value == prev.value {
					add = false
				}
			}
			if n.value == prev.value {
				add = false
			}
			if add {
				n.prev = append(n.prev, prev)
			}
		}
	}
}

func printNodes(nodes []*node) {
	for i, n := range nodes {
		fmt.Printf("%d: %s -> ", i, n.value)
		for _, next := range n.next {
			fmt.Printf("%s ", next.value)
		}
		fmt.Print(" <- ")
		for _, prev := range n.prev {
			fmt.Printf("%s ", prev.value)
		}
		fmt.Println()
	}
}

func main() {
	if len(os.Args) < 4 {
		fmt.Printf("Usage: %s <filename> <min-size> <max-size> <used>", os.Args[0])
		return
	}
	filename := os.Args[1]
	minSize, err := strconv.Atoi(os.Args[2])
	if err != nil {
		fmt.Println("Error parsing end-size")
		return
	}
	maxSize, err := strconv.Atoi(os.Args[3])
	if err != nil {
		fmt.Println("Error parsing end-size")
		return
	}
	var used int = 0
	if len(os.Args) == 5 {
		used, err = strconv.Atoi(os.Args[4])
		if err != nil {
			fmt.Println("Error parsing used")
			return
		}
	}
	lines, err := readLines(filename)
	if err != nil {
		fmt.Println("Error reading file")
		return
	}
	nodes := nodes(lines)

	debug := os.Getenv("DNA_DEBUG") == "1"
	if debug {
		printNodes(nodes)
	}

	for offset := 0; offset != wordSize-1; offset++ {
		incresaOffset(nodes, offset)
		resetUsed(nodes)
		nodes = mergeAll(nodes, []*node{}, offset)
		started := getStarted(nodes)
		if debug {
			fmt.Printf("Iteration %d\n", offset)
			printNodes(nodes)
			fmt.Println("Started..")
			for _, n := range started {
				fmt.Println(n.value)
			}
		}
		for _, n := range started {
			resetUsed(nodes)
			solutions := getSolutions(n, solution{n.value, n.count})
			for _, s := range solutions {
				if len(s.value) >= minSize && len(s.value) <= maxSize {
					if used == 0 || s.count == used {
						fmt.Printf("Solution it - %d size - %d used - %d: %s\n", offset, len(s.value), s.count, s.value)
            return
					}
				}
			}
		}
	}
}
