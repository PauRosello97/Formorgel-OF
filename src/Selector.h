#pragma once
#include "ofMain.h";
#include "SmallButton.h";

class Selector
{
	float x, y;
	float w = 175;
	float h = 30;
	SmallButton previousButton;
	SmallButton nextButton;
	int value = 0;
	int nValues;
	vector<string> valueNames;
	ofTrueTypeFont openSans;

	void drawPreviousArrow(float ax, float ay);
	void drawNextArrow(float ax, float ay);
	bool isOverPrevious();
	bool isOverNext();
	
public:
	
	Selector() {};
	Selector(float _x, float _y, vector<string> _valueNames);

	void display();
	bool mousePressed();
	int getValue() { return value; }
};

