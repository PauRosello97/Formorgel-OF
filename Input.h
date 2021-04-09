#pragma once
#include "ofMain.h"

class Input
{
	float x, y;
	float w = 150;
	float h = 50;
	
public:
	Input(){};
	Input(float& _value, float _x, float _y) : value(_value){
		x = _x;
		y = _y;
	};
	void display();
	bool isOver();
	void mousePressed();
	float value;
	
};

