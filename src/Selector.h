#pragma once
#include "ofMain.h"
#include "SmallButton.h"

class Selector
{
	float x, y;
	float w = 360;
	float h = 50;
	SmallButton previousButton;
	SmallButton nextButton;
	int value = 0;
	int nValues;
	vector<string> valueNames;
	
public:
	
	Selector() {};
	Selector(float _x, float _y, vector<string> _valueNames);

	void display();
	bool mousePressed();
	int getValue() { return value; }
};

