#pragma once
#include "ofMain.h"

class Input
{
	float x, y;
	float w = 150;
	float h = 50;
	//float& value;

public:
	Input();
	Input(float x, float y);
	void display();
	bool isOver();
	void mousePressed();
	
};

