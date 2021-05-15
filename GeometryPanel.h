#pragma once
#include "ofMain.h"
#include "Osc.h"
#include "FloatInput.h"

class GeometryPanel
{
	float x = 10;
	float y = 50;
	FloatInput iterationsInput;
	
public:
	Osc oscA;
	Osc oscB;
	Osc oscC;
	float iterations = 1;
	
	float w = 400;
	//Si es canvia w, cal canviar els constructors Osc
	GeometryPanel() : 
		oscA(x, y+70, 400, 0), 
		oscB(x, y+280, 400, 0), 
		oscC(x, y+490, 400), 
		iterationsInput(iterations, "Iterations", x, y+10, 1, 0, 4) {};

	void display() {
		oscA.display();
		oscB.display();
		oscC.display();
		iterationsInput.display();
	}

	bool mousePressed();
};

