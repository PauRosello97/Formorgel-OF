#include "Triangle.h"

Triangle::Triangle(Node _p1, Node _p2, Node _p3) {
	p1 = _p1;
	p2 = _p2;
	p3 = _p3;
	triangleColor = ofColor(ofRandom(100, 255), ofRandom(255), ofRandom(255));
}

ofVec2f Triangle::center() {
	LineIntersector lineIntersector;
	return lineIntersector.simpleIntersect(p1.pos.x, p1.pos.y, (p2.pos.x + p3.pos.x) * .5, (p2.pos.y + p3.pos.y) * .5, p2.pos.x, p2.pos.y, (p3.pos.x + p1.pos.x) * .5, (p3.pos.y + p1.pos.y) * .5);
}

bool Triangle::equals(Triangle other) {
	return p1.equals(other.p1) && p2.equals(other.p2) && p3.equals(other.p3);
}

void Triangle::draw() {
	ofSetColor(triangleColor);
	ofDrawTriangle(p1.pos, p2.pos, p3.pos);
}