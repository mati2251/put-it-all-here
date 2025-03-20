package heu

import (
	"math"
	"path-search/graph"
)

// BFS is optimal when the heuristic is lower or equal to the cost of the path (such algorithm is called A*)
func BFS(start *graph.Node) []string {
	open := []*graph.Edge{}
	for _, edge := range *start.Edges {
		open = append(open, &edge)
	}
	path := make(map[string][]string, 0)
  path[start.Name] = []string{start.Name}
	return bfs(open, &path)
}

func bfs(open []*graph.Edge, path *map[string][]string) []string {
	if len(open) == 0 {
		return nil
	}
	edge, open := getTheLowestHeuristic(open)
	(*path)[edge.To.Name] = append((*path)[edge.From.Name], edge.To.Name)
	if edge.To.Goal {
		return (*path)[edge.To.Name]
	}
	for _, edge := range *edge.To.Edges {
		open = append(open, &edge)
	}
	return bfs(open, path)
}

func getTheLowestHeuristic(open []*graph.Edge) (*graph.Edge, []*graph.Edge) {
	lowestIndex := 0
	lowestValue := math.MaxInt16
	for index, edge := range open {
		if lowestValue > getHeuristic(*edge) {
			lowestValue = getHeuristic(*edge)
			lowestIndex = index
		}
	}
  lowestEdge := *open[lowestIndex]
	open[lowestIndex], open[len(open)-1] = open[len(open)-1], open[lowestIndex]
	return &lowestEdge, open[:len(open)-1]
}

func getHeuristic(node graph.Edge) int {
	if node.To.Goal {
		return 0
	}
	return node.Weight
}
