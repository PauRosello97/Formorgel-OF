#pragma once

#include "Node.h"
#include "LineIntersector.h"

class Triangle
{
	public: 
		Triangle(Node p1, Node p2, Node p3);
		ofVec2f center();
		bool equals(Triangle other);
		void draw();
		ofColor triangleColor;

		Node p1, p2, p3;
};

