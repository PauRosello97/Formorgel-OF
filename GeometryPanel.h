#pragma once
#include "ofMain.h"
#include "Osc.h"

class GeometryPanel
{
	float x = 10;
	float y = 50;
	
public:
	Osc oscA;
	Osc oscB;
	float w = 400;
	//Si es canvia w, cal canviar els constructors Osc
	GeometryPanel() : oscA(x, y, 400), oscB(x, y+210, 400) {};

	void display() {
		oscA.display();
		oscB.display();
	}

	bool mousePressed();
};

