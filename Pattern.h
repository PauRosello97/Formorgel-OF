#pragma once

#include "ofMain.h"
#include "Node.h"
#include "Line.h"
#include "Triangle.h"
#include "Triangulator.h"

class Pattern
{
public:
	Pattern();
	void setup(ofShader shader);
	void draw();
	void setDoShader(bool doShader);
	void generateLines();
	void findIntersections();
	void generateTriangles();
	int getNLines();
	int getNNodes();
	int getNTriangles();

	ofShader shader;
	bool doShader;
	bool displayTriangles;
	vector<ofVec2f> points;
	vector<Line> lines;
	vector<Node> intersections;
	vector<Triangle> triangles;
	int num;
};

