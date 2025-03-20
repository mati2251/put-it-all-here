package main

import (
	"fmt"
	"path-search/graph"
	"path-search/heuristic"
	"path-search/non-heuristic"
)

func main() {
	root := graph.TestGraph()
	graph.PrintGraph(root)
  fmt.Println("Non-heuristic search")
  dfsKeys := non.DFSfirst(root)
  fmt.Println(dfsKeys)
  bfsKeys := non.BFS(root)
  fmt.Println(bfsKeys)
  idsKeys := non.IterativeDeeping(root, 4)
  fmt.Println(idsKeys)
  ucsKeys := non.UCS(root)
  fmt.Println(ucsKeys)
  fmt.Println("Heuristic search")
  climbingKeys := heu.Climbing(root)
  fmt.Println(climbingKeys)
  bfsKeys = heu.BFS(root)
  fmt.Println(bfsKeys)
}
