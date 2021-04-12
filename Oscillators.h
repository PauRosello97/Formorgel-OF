#pragma once
#include "ofMain.h"
#include "Osc.h"

class Oscillators
{
	Osc oscA;
	//Osc oscB;

public:
	//Oscillators() : oscA(10, 10), oscB(10, 200) {};
	Oscillators() : oscA(10, 10) {};

	void display() {
		oscA.display();
		//oscB.display();
	}

	void mousePressed();

};

