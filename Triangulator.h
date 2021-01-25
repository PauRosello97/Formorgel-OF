#pragma once

#include "Node.h"
#include "Triangle.h"
#include "CircumCircle.h"
#include "Edge.h"
#include <algorithm>

class Triangulator
{	
		bool sharedVertex(Triangle t1, Triangle t2);
		void sortXList(vector<Node> ps);
		void sortXArray(vector<ofVec2f> ps);

	public:
		vector<Triangle> triangulate(vector<Node> pxyz);
};
