package non

import (
	"path-search/graph"
)

type UCSNode struct{
  node *graph.Node
  cost int
  path []string
}

func UCS(g *graph.Node) (path []string) {
	open := make([]*UCSNode, 0)
  open = append(open, &UCSNode{node: g, cost: 0, path: []string{g.Name}})
  return ucs(open)
}

func ucs(open []*UCSNode) (path []string) {
  if len(open) == 0 {
    return nil
  }
  node, open := getLowestCost(open) 
  if node.node.Goal {
    return node.path
  }
  for _, edge := range *node.node.Edges {
    open = append(open, &UCSNode{node: edge.To, cost: node.cost + edge.Weight, path: append(node.path, edge.To.Name)})
  }
  return ucs(open)
}

func getLowestCost(open []*UCSNode) (*UCSNode, []*UCSNode) {
  lowest := open[0]
  lowestIndex := 0
  for index, node := range open {
    if node.cost < lowest.cost {
      lowest = node
      lowestIndex = index
    }
  }
  open[lowestIndex] = open[len(open)-1]
  open = open[:len(open)-1]
  return lowest, open
}
