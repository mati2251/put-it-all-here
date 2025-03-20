package non

import "path-search/graph"

func IterativeDeeping(start *graph.Node, depth int) []string {
  for i := 0; i <= depth; i++ {
    path := make([]string, 0)
    result := dfs(start, 0, i, path)
    if result != nil {
      return result 
    }
  }
  return nil
}

func dfs(node *graph.Node, currentDepth int, depth int, path []string) []string {
  path = append(path, node.Name)
  if currentDepth == depth {
    return nil 
  }
  if node.Goal {
    return path 
  }
  for _, edge := range *node.Edges {
    path := dfs(edge.To, currentDepth + 1, depth, path) 
    if path != nil {
      return path 
    }
  }
  return nil
}

