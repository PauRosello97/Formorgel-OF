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
	Oscillators() : oscA(10, 25, 400), oscB(10, 235, 400) {};

	void display() {
		oscA.display();
		oscB.display();
	}

	bool mousePressed();
};

