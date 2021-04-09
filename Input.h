#pragma once
#include "ofMain.h"

class Input
{
	float x, y;
	float w = 150;
	float h = 50;
	//float& value;

public:
	Input(){};
	Input(float _x, float _y){
		x = _x;
		y = _y;
	};
	void display();
	bool isOver();
	void mousePressed();
	
};

