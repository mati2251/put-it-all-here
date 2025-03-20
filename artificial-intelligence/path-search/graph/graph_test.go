package graph

import "testing"

func TestGenerateDepth(t *testing.T) {
	root := Generate(10)
	depth := 0
	for node := root; node != nil; {
		if node.Goal == true {
			node = nil
		} else {
			node = (*node.Edges)[0].To
			depth++
		}
	}
	if depth != 10 {
		t.Errorf("Expected depth of 10, got %d", depth)
	}
}

func TestGenerateVertexAtLeastOne(t *testing.T) {
	root := Generate(15)
	testGenerateVertexAtLeastOneR(t, root)
}

func testGenerateVertexAtLeastOneR(t *testing.T, start *Node) {
	if start.Goal == true {
		return
	}
	if len(*start.Edges) == 0 {
		t.Errorf("Expected at least one edge, got 0")
	}
	for _, edge := range *start.Edges {
		testGenerateVertexAtLeastOneR(t, edge.To)
	}
}