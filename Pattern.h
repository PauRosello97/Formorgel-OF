#pragma once

#include "ofMain.h"
#include "Node.h"
#include "Line.h"

class Pattern
{
public:
	Pattern();
	void setup(ofShader shader);
	void draw();
	void setDoShader(bool doShader);
	void generateLines();
	void findIntersections();
	int getLinesSize();

	ofShader shader;
	bool doShader;
	vector<ofVec2f> points;
	vector<Line> lines;
	vector<Node> intersections;
	int num;
};

