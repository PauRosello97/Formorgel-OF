#pragma once
#include "ofMain.h"
#include <string> 

class ColorAreaAssignation
{
public:
	int area;
	ofColor color;

	ColorAreaAssignation(int _area, int r, int g, int b) {
		area = _area;
		color = ofColor(r, g, b);
	};

	string toString() {
		return to_string(area) + " = (" + to_string(color.r) + ", " + to_string(color.g) + ", " + to_string(color.b) + ")";
	}
};