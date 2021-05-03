#pragma once
#include "ofMain.h"
#include "SmallButton.h"

class ModeSelector
{
	float x, y;
	float w = 380;
	float h = 50;
	SmallButton previousButton;
	SmallButton nextButton;
	int mode = 0;
	vector<string> modeNames = { "Lydian", "Ionian", "Mixolydian", "Dorian", "Aeolian", "Phrygian", "Locrian" };
	
public:
	
	ModeSelector() {};
	ModeSelector(float _x, float _y) {
		x = _x;
		y = _y;
		previousButton = SmallButton(x+h/2, y+h/2, h-20);
		nextButton = SmallButton(x+w-h/2, y+h/2, h-20);
	};

	void display() {
		// Text
		ofSetColor(0);
		ofDrawBitmapString(ofToString(mode) + " " + modeNames[mode], x + 50, y + 30);

		// Buttons
		previousButton.display();
		nextButton.display();

		// Background
		ofSetColor(200);
		ofDrawRectangle(x, y, w, h);
	}

	bool mousePressed() {
		if (previousButton.isOver()) {
			mode = mode > 0 ? mode - 1 : 6;
			return true;
		}
		else if (nextButton.isOver()) {
			mode = (mode + 1) % 7;
			return true;
		}
		return false;
	}

	int getMode() {
		return mode;
	}
};

