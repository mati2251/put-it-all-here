package heu

import (
	"path-search/graph"
)

func Climbing(start *graph.Node) []string {
	path := []string{start.Name}
	return climbing(start, path)
}

func climbing(g *graph.Node, path []string) []string {
	path = append(path, g.Name)
	if g.Goal {
		return path
	}
	neighbors := g.Edges
  if len(*neighbors) == 0 {
    return []string{} 
  }
	best := getBestNeighbor(neighbors)
	return climbing(best.To, path)
}

func getBestNeighbor(neighbors *[]graph.Edge) graph.Edge {
	best := (*neighbors)[0] 
	for _, n := range *neighbors {
		if n.Weight < best.Weight {
			best = n
		}
	}
	return best
}
