#pragma once
#include "ofMain.h"

class Touchable
{
	

public:
	float x, y, h, w;

	bool isOver() {
		return ofGetMouseX() > x&& ofGetMouseX() < x + w && ofGetMouseY() > y&& ofGetMouseY() < y + h;
	}
};

