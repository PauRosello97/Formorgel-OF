#pragma once
#include "ofMain.h"
#include "Osc.h"

class GeometryPanel
{
	
public:
	Osc oscA;
	Osc oscB;
	float w = 400;
	//Si es canvia w, cal canviar els constructors Osc
	GeometryPanel() : oscA(10, 50, 400), oscB(10, 260, 400) {};

	void display() {
		oscA.display();
		oscB.display();
	}

	bool mousePressed();
};

