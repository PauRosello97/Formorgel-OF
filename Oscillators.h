#pragma once
#include "ofMain.h"
#include "Osc.h"

class Oscillators
{
	
public:
	Osc oscA;
	Osc oscB;
	float w = 400;
	//Si es canvia w, cal canviar els constructors Osc
	Oscillators() : oscA(10, 50, 400), oscB(10, 260, 400) {};

	void display() {
		oscA.display();
		oscB.display();
	}

	bool mousePressed();
};

