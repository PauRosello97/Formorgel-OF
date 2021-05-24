#pragma once
#include "ofMain.h";

class GeometryColorSwitch
{
	string mode = "color";
	float x = 10;
	float y = 10;
	float w = 380;
	float h = 40;

public:
	void display();
	bool isOverA();
	bool isOverB();
	bool mousePressed();
	bool inGeometryMode();
};


