#pragma once
#include "ofMain.h";

class PolygonColorControl
{
	float x;
	float y;
	float w = 100;
	float h = 100;
	ofColor color;
	int area;
	vector<ofColor>& colors;

public:
	//PolygonColorControl(){}
	PolygonColorControl(float _x, float _y, int _area, ofColor _color, vector<ofColor>& _colors) : colors(_colors) {
		x = _x;
		y = _y;
		color = _color;
		area = _area;
	};

	void display();
	bool isOver();
	void mousePressed();
};

