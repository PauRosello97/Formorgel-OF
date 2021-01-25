#pragma once

#include "Node.h"

class Edge {
public:
	Edge();
	Edge(Node p1, Node p2);

	Node p1, p2;
};
