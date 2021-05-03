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
	vector<Tone>& tones;
	vector<int> modeMatrix;
	
public:
	bool displayingDialog;
	//PolygonColorControl(){}
	PolygonColorControl(
		float _x, 
		float _y, 
		int _area, 
		Tone _tone, 
		vector<Tone>& _tones, 
		vector<int> _modeMatrix
	) : tones(_tones) {
		modeMatrix = _modeMatrix;
		x = _x;
		y = _y;
		area = _area;
		displayingDialog = false;
		tone = _tone;
		setColor();
	};

	void display();
	bool isOver();
	bool mousePressed();
	void setColor(ofColor c);
	void setModeMatrix(vector<int> modeMatrix);
	void setColor();
	ofColor getColor();
	
};

