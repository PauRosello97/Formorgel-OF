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

public:
	PolygonColorControl(){}
	PolygonColorControl(float _x, float _y, int _area, ofColor _color);
	void display();
	bool isOver();
	void mousePressed();
};

