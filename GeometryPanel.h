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
	Osc oscC;
	float w = 400;
	//Si es canvia w, cal canviar els constructors Osc
	GeometryPanel() : oscA(x, y, 400, 0), oscB(x, y+210, 400, 0), oscC(x, y+420, 400) {};

	void display() {
		oscA.display();
		oscB.display();
		oscC.display();
	}

	bool mousePressed();
};

