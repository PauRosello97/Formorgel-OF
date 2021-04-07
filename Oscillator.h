#pragma once
#include "ofMain.h"
#include "Button.h"

class Oscillator
{
	Button button;
	float x, y, h, w;

public:
	Oscillator();
	Oscillator(float x, float y, float w, float h);
	void display();
};

