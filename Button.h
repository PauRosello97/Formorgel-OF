#pragma once
#include "ofMain.h"

class Button
{
	float x, y, h, w;

public:
	Button();
	Button(float x, float y, float w, float h);
	void display();
	bool isOver();
};

