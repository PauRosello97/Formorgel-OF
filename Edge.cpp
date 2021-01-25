#include "Edge.h"

Edge::Edge() {
	p1 = p2 = Node();
}

Edge::Edge(Node _p1, Node _p2) {
	p1 = _p1;
	p2 = _p2;
}