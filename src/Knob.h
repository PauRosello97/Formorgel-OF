#pragma once
#include "ofMain.h"
#include "Touchable.h"

class Knob : public Touchable
{
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
	void mousePressed();
	bool mouseReleased();
	bool isPressed() { return pressed; }

};

