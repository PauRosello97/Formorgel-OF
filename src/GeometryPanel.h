#pragma once
#include "ofMain.h"
#include "Osc.h"
#include "FloatInput.h"
#include "Button.h"

class GeometryPanel
{
	float x = 10;
	float y = 50;
	FloatInput iterationsInput;
	Button randomizeButton;
	void randomize();

public:
	Osc oscA;
	Osc oscB;
	Osc oscC;
	float iterations = 1;
	
	float w = 400;
	//Si es canvia w, cal canviar els constructors Osc
	GeometryPanel() : 
		oscA(x, y+50, 400, 0), 
		oscB(x, y+260, 400, 0), 
		oscC(x, y+470, 400), 
		iterationsInput(iterations, "Iterations", x, y+10, 1, 0, 4) 
	{
		randomizeButton = Button(x+200, y+10, 200, 30);
	};

	void display();
	bool mousePressed();
};

