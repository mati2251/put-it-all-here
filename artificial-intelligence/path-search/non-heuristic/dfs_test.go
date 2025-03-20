package non 

import (
	"path-search/graph"
	"reflect"
	"testing"
)

func TestDFS(t *testing.T) {
	root := graph.TestGraph()
	result := DFSfirst(root)
	expected := []string{"A", "B", "F", "J"}
	if !reflect.DeepEqual(result, expected) {
		t.Errorf("Expected %v, got %v", expected, result)
	}
}

func TestDFSAll(t *testing.T) {
	root := graph.TestGraph()
	result := DFSOptimal(root)
	expected := []string{"A", "C", "H", "I", "K"}
	if !reflect.DeepEqual(result, expected) {
		t.Errorf("Expected %v, got %v", expected, result)
	}
}
