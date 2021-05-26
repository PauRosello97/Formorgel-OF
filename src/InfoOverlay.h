#pragma once
#include "ofMain.h"
#include "Touchable.h"

class InfoOverlay : public Touchable
{
	ofTrueTypeFont openSans;

public:
	InfoOverlay();
	void display();
};

