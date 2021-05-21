#pragma once
#include "ofMain.h"

class DragController
{
	float x, y, h, w;
	bool pressed = false;
	float initialX;
	float& value;

	void update();

public:

	DragController(float& v, float x, float y, float w, float h);
	void display();
	bool isOver();
	void mousePressed();
	bool mouseReleased();
	bool isPressed() { return pressed; }
};

