#pragma once
#include "ofMain.h";

class GeometryColorSwitch
{
	string mode = "geometry";
	float x = 10;
	float y = 10;
	float w = 380;
	float h = 40;
	ofTrueTypeFont openSans;

public:
	GeometryColorSwitch();
	void display();
	bool isOverA();
	bool isOverB();
	bool mousePressed();
	bool inGeometryMode();
};


