#pragma once
#include "ofMain.h"

class Button
{
	float x, y, h, w;
	ofTrueTypeFont openSans;

public:
	Button();
	Button(float x, float y, float w, float h);
	void display(string message);
	bool isOver();
	bool mousePressed();
};

