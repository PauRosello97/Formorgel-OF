#pragma once
#include "ofMain.h"
#include "Touchable.h"
#include "ofxSvg.h"

class InfoButton : public Touchable
{
	ofxSVG lightLogo;
	ofxSVG darkLogo;

public:
	InfoButton() {};
	InfoButton(float x, float y, float w, float h);
	void display();
	bool mousePressed();
};

