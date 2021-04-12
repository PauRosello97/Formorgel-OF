#pragma once
#include "ofMain.h"
#include "Button.h"
#include "Input.h"

class Oscillator
{
	Button button;
	//Input angleInput;
	float x, y, h, w;
	float o = 50;

public:
	Oscillator() {};
	Oscillator(float _x, float _y, float _w, float _h) {
		x = _x;
		y = _y;
		w = _w;
		h = _h;
		button = Button(x + 2 * w / 3, y + h - 30, w / 3, 30);
	};

	void display();
	bool isOverButton();
	void mousePressed();

	float offset = 0;
	float angle = ofRandom(90);
	float length = 2;
	
};

