package non 

import (
	"path-search/graph"
)

func BFS(start *graph.Node) []string {
	queue := make([]*graph.Node, 0)
	queue = append(queue, start)
  visited := make(map[string]bool)
  path := make(map[string][]string)
  path[start.Name] = []string{}
  node := bfsr(start, visited, queue, path)
  return append(path[node.Name], node.Name)
}

func bfsr(start *graph.Node, visited map[string]bool, queue []*graph.Node, path map[string][]string) *graph.Node {
  if start.Goal == true {
    return start 
  }
  visited[start.Name] = true
  for _, edge := range *start.Edges {
    queue = append(queue, edge.To)
    path[edge.To.Name] = append(path[edge.From.Name], start.Name)
  }
  return bfsr(queue[0], visited, queue[1:], path)
}
