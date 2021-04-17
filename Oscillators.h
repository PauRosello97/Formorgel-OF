#pragma once
#include "ofMain.h"
#include "Osc.h"

class Oscillators
{
	
public:
	Osc oscA;
	Osc oscB;

	Oscillators() : oscA(10, 10), oscB(10, 300) {};

	void display() {
		oscA.display();
		oscB.display();
	}

	void mousePressed();

};

