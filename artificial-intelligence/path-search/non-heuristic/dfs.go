package non 

import (
	"math"
	"path-search/graph"
)

func DFSfirst(start *graph.Node) []string {
	result := make([]string, 0)
	visited := make(map[string]bool)
	goal := false
	dfsrFirst(start, visited, &result, &goal)
	return result
}

func dfsrFirst(start *graph.Node, visited map[string]bool, result *[]string, goal *bool) {
	visited[start.Name] = true
	*result = append(*result, start.Name)
	for _, edge := range *start.Edges {
		if !visited[edge.To.Name] && !*goal {
			dfsrFirst(edge.To, visited, result, goal)
		}
	}
	if start.Goal || *goal {
		*goal = true
		return
	}
	*result = (*result)[:len(*result)-1]
}

func DFSOptimal(start *graph.Node) []string {
	current := make([]string, 0)
	currentPrice := int32(0)
	visited := make(map[string]bool)
	result := make([]string, 0)
	var resultPrice int32 = math.MaxInt32
	dfsrOptimal(start, visited, &current, &currentPrice, &result, &resultPrice)
	return result
}

func dfsrOptimal(start *graph.Node, visited map[string]bool, current *[]string, currentPrice *int32, result *[]string, resultPrice *int32) {
	visited[start.Name] = true
	*current = append(*current, start.Name)
	for _, edge := range *start.Edges {
		if !visited[edge.To.Name] {
			*currentPrice += int32(edge.Weight)
			dfsrOptimal(edge.To, visited, current, currentPrice, result, resultPrice)
			*currentPrice -= int32(edge.Weight)
		}
	}
	if start.Goal && *currentPrice < *resultPrice {
		*resultPrice = *currentPrice
		*result = make([]string, len(*current))
		copy(*result, *current)
	}
	*current = (*current)[:len(*current)-1]
}
