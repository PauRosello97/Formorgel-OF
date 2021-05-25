#pragma once
#include "ofMain.h"
#include "Touchable.h"

class InfoButton : public Touchable
{

public:
	InfoButton() {};
	InfoButton(float x, float y, float w, float h);
	void display();
	bool mousePressed();
};

