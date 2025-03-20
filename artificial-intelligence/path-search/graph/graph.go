package graph

import (
	"fmt"
	"math/rand"
	"os"
	"slices"
	"strings"
)

type Node struct {
	Name  string
	Edges *[]Edge
	Goal  bool
}

type Edge struct {
	Weight int
	To     *Node
	From   *Node
}

const NONE_COLOR = "\033[0m"
const GREEN_COLOR = "\033[0;32m"
const RED_COLOR = "\033[0;32m"

func generateR(start *Node, depth int, currDepth int) {
	degreeLevel := rand.Intn(4) + 1
	edges := make([]Edge, degreeLevel)
	if currDepth == depth {
		start.Edges = &[]Edge{}
		return
	}
	for deg := 1; deg <= degreeLevel; deg++ {
		edges[deg-1] = Edge{
			Weight: rand.Intn(20) + 1,
			From:   start,
			To:     &Node{Name: start.Name + "." + fmt.Sprint(deg), Goal: false},
		}
		generateR(edges[deg-1].To, depth, currDepth+1)
	}
	start.Edges = &edges
}

func setGoalState(start *Node) {
	degree := len(*start.Edges)
	if degree == 0 {
		start.Goal = true
		return
	}
	nextIndex := rand.Intn(degree)
	for index, edge := range *start.Edges {
		if nextIndex == index {
			setGoalState(edge.To)
		}
	}

}

func Generate(depth int) *Node {
	start := Node{Name: "node"}
	generateR(&start, depth, 0)
	for i := 0; i < depth; i++ {
		setGoalState(&start)
	}
	return &start
}

func printGraphR(start *Node, gap string, path *[]string, goal *bool) {
	ovrGap := gap
	if lastIndex := strings.LastIndex(ovrGap, "  "); lastIndex != -1 {
		ovrGap = ovrGap[:lastIndex-1] + "|" + NONE_COLOR + "--" + ovrGap[lastIndex+2:]
	}
	if *goal {
		ovrGap = strings.ReplaceAll(ovrGap, GREEN_COLOR, "")
	}
	if slices.Contains(*path, start.Name) {
		ovrGap = strings.ReplaceAll(ovrGap, NONE_COLOR, "")
		fmt.Fprintf(os.Stdout, "%s%s%s%s\n", ovrGap, GREEN_COLOR, start.Name, NONE_COLOR)
		gap = strings.ReplaceAll(gap, RED_COLOR, NONE_COLOR)
		gap += RED_COLOR + "|  " + NONE_COLOR
		if start.Goal {
			*goal = true
		}
	} else {
		fmt.Fprintf(os.Stdout, "%s%s\n", ovrGap, start.Name)
		gap += "|  "
	}
	for index, edge := range *start.Edges {
		if edge.To == nil {
			continue
		}
		if index == len(*start.Edges)-1 {
			if lastIndex := strings.LastIndex(gap, "|  "); lastIndex != -1 {
				gap = gap[:lastIndex] + "   " + gap[lastIndex+3:]
			}
		}
		printGraphR(edge.To, gap, path, goal)
	}
}

func PrintGraphMark(start *Node, path *[]string) {
	goal := false
	printGraphR(start, "", path, &goal)
}

func PrintGraph(start *Node) {
	goal := false
	empty := []string{}
	printGraphR(start, "", &empty, &goal)
}

func TestGraph() *Node {
	a := Node{Name: "A", Goal: false}
	b := Node{Name: "B", Goal: false}
	c := Node{Name: "C", Goal: false}
	d := Node{Name: "D", Goal: false}
	e := Node{Name: "E", Goal: false}
	f := Node{Name: "F", Goal: false}
	g := Node{Name: "G", Goal: false}
	h := Node{Name: "H", Goal: false}
	i := Node{Name: "I", Goal: false}
	j := Node{Name: "J", Goal: true}
	k := Node{Name: "K", Goal: true}
	a.Edges = &[]Edge{
		{Weight: 4, To: &b, From: &a},
		{Weight: 3, To: &c, From: &a},
		{Weight: 3, To: &d, From: &a},
	}
	b.Edges = &[]Edge{
		{Weight: 2, To: &e, From: &b},
		{Weight: 10, To: &f, From: &b},
	}
	c.Edges = &[]Edge{
		{Weight: 3, To: &f, From: &c},
		{Weight: 3, To: &h, From: &c},
	}
	d.Edges = &[]Edge{
		{Weight: 2, To: &h, From: &d},
	}
	e.Edges = &[]Edge{}
	f.Edges = &[]Edge{
		{Weight: 2, To: &g, From: &f},
		{Weight: 3, To: &j, From: &f},
	}
	g.Edges = &[]Edge{}
	h.Edges = &[]Edge{
		{Weight: 1, To: &i, From: &h},
	}
	i.Edges = &[]Edge{
		{Weight: 1, To: &k, From: &i},
	}
	j.Edges = &[]Edge{}
	k.Edges = &[]Edge{}
	return &a
}
