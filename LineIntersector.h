#pragma once

#include "ofMain.h"

class LineIntersector
{
	public:
		LineIntersector();
		bool intersect(float a_x1, float a_y1, float a_x2, float a_y2, float b_x1, float b_y1, float b_x2, float b_y2, ofVec2f p);
		ofVec2f simpleIntersect(float a_x1, float a_y1, float a_x2, float a_y2, float b_x1, float b_y1, float b_x2, float b_y2);
};

