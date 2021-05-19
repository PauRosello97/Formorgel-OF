#pragma once
#include "ofMain.h"
#include "SmallButton.h"

class Selector
{
	float x, y;
	float w = 380;
	float h = 50;
	SmallButton previousButton;
	SmallButton nextButton;
	int value = 0;
	int nValues;
	vector<string> valueNames;
	
public:
	
	Selector() {};
	Selector(float _x, float _y, vector<string> _valueNames) {
		x = _x;
		y = _y;
		previousButton = SmallButton(x+h/2, y+h/2, h-20);
		nextButton = SmallButton(x+w-h/2, y+h/2, h-20);
		valueNames = _valueNames;
		nValues = valueNames.size();
	};

	void display() {
		// Text
		ofSetColor(0);
		ofDrawBitmapString(ofToString(value) + " " + valueNames[value], x + 50, y + 30);

		// Buttons
		previousButton.display();
		nextButton.display();

		// Background
		ofSetColor(200);
		ofDrawRectangle(x, y, w, h);
	}

	bool mousePressed() {
		if (previousButton.isOver()) {
			value = value > 0 ? value - 1 : (nValues-1);
			return true;
		}
		else if (nextButton.isOver()) {
			value = (value + 1) % nValues;
			return true;
		}
		return false;
	}

	int getValue() {
		return value;
	}
};

