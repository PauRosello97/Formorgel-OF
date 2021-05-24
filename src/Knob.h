#pragma once
#include "ofMain.h"

class Knob
{
	float x, y, h, w;
	bool pressed = false;
	float initialX;
	float& value;
	float min, max;
	float initialValue;
	float sensibility;
	int knobRadius = 20;
	ofTrueTypeFont openSans;

	void update();

public:

	Knob(float& v, float x, float y, float w, float h, float min, float max);
	void display();
	bool isOver();
	void mousePressed();
	bool mouseReleased();
	bool isPressed() { return pressed; }

};

