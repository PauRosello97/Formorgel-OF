#pragma once
#include "ofMain.h";
#include "Tone.h";

class PolygonColorControl
{
	float x;
	float y;
	float w = 100;
	float h = 100;
	Tone tone;
	ofColor color;
	int area;
	vector<ofColor>& colors;
	
public:
	bool displayingDialog;
	//PolygonColorControl(){}
	PolygonColorControl(float _x, float _y, int _area, ofColor _color, Tone _tone, vector<ofColor>& _colors) : colors(_colors) {
		x = _x;
		y = _y;
		
		area = _area;
		displayingDialog = false;
		tone = _tone;
		color.setHsb(tone.number * 30, 255, tone.luminance*2.5);
	};

	void display();
	bool isOver();
	bool mousePressed();
	void setColor(ofColor c);
};

