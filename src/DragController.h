#pragma once
#include "ofMain.h"

class DragController
{
	float x, y, h, w;
	bool pressed = false;
	float initialX;
	float& value;
	float step, min, max;
	float initialValue;
	float sensibility;

	void update();

public:

	DragController(float& v, float x, float y, float w, float h, float step, float min, float max);
	void display();
	bool isOver();
	void mousePressed();
	bool mouseReleased();
	bool isPressed() { return pressed; }
};

