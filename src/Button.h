#pragma once
#include "ofMain.h"
#include "Touchable.h"

class Button : public Touchable
{
	ofTrueTypeFont openSans;

public:
	Button();
	Button(float x, float y, float w, float h);
	void display(string message);
	bool mousePressed();
};

