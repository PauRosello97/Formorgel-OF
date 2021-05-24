#pragma once
#include "ofMain.h";
#include "SmallButton.h";
#include "ofxSvg.h";

class Selector
{
	float x, y;
	float w = 175;
	float h = 50;
	SmallButton previousButton;
	SmallButton nextButton;
	int value = 0;
	int nValues;
	vector<string> valueNames;
	ofxSVG arrowPrevious;
	
public:
	
	Selector() {};
	Selector(float _x, float _y, vector<string> _valueNames);

	void display();
	bool mousePressed();
	int getValue() { return value; }
};

