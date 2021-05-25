#pragma once
#include "ofMain.h"
#include "Osc.h"
#include "FloatInput.h"
#include "Button.h"
#include "Selector.h"

class GeometryPanel
{
	float x = 10;
	float y = 50;
	FloatInput iterationsInput;
	Button randomizeButton;
	void randomize();
	Selector iterationsSelector = Selector(
		x + 10,
		y + 10,
		{ "0 iterations", "1 iteration", "2 iterations", "3 iterations" }
	);

public:
	Osc oscA;
	Osc oscB;
	Osc oscC;
	float iterations = 0;
	
	float w = 380;
	float h = 740;
	//Si es canvia w, cal canviar els constructors Osc
	GeometryPanel() : 
		oscA(x, y+60, 380, 220, 0), 
		oscB(x, y+290, 380, 220, 0), 
		oscC(x, y+520, 380, 220), 
		iterationsInput(iterations, "Iterations", x, y+10, 0, 4) 
	{
		randomizeButton = Button(x+250, y+10, 120, 30);
	};

	void display();
	bool mousePressed();
	bool mouseReleased();
};

