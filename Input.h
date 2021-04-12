#pragma once
#include "ofMain.h"

class Input
{
	float x, y;
	float w = 150;
	float h = 50;
	float& value;
	
public:
	Input() : value(h) {};
	Input(float& v, float _x, float _y) : value(v){
		x = _x;
		y = _y;
	};
	void display();
	bool isOver();
	void mousePressed();
	
	
};

