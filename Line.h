#pragma once
#include "ofMain.h"
#include "Node.h"

class Line
{
	public:
		Line(ofVec2f start, ofVec2f end, int id);
		void draw();
		Node intersectsAt(Line other);
		Node lineIntersection(Line other);
		

		ofVec2f start, end;
		float m, n;
		int id;
};

