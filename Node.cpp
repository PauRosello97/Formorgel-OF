#include "Node.h"


Node::Node(float x, float y) {
	isNull = false;
	pos.set(x, y);
}

Node::Node() {
	isNull = true;
}

void Node::draw() {
	ofDrawCircle(pos, 10);
}

bool Node::getIsNull() {
	return isNull;
}