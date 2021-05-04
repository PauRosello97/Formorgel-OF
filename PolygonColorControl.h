#pragma once
#include "ofMain.h";
#include "Tone.h";

class PolygonColorControl
{
	float x;
	float y;
	float w = 100;
	float h = 100;
	int baseHue;
	Tone tone;
	ofColor color;
	int area;
	vector<Tone>& tones;
	vector<int> modeMatrix;
	vector<string> romanNumbers = {"I", "II", "III", "IV", "V", "VI", "VII"};
	
public:
	bool displayingDialog;
	//PolygonColorControl(){}
	PolygonColorControl(
		float _x, 
		float _y, 
		int _area, 
		Tone _tone, 
		vector<Tone>& _tones, 
		vector<int> _modeMatrix,
		int baseTone
	) : tones(_tones) {
		modeMatrix = _modeMatrix;
		x = _x;
		y = _y;
		area = _area;
		displayingDialog = false;
		tone = _tone;
		setColor();
		baseHue = baseTone * 30;
	};

	void display();
	bool isOver();
	bool mousePressed();
	void setColor(ofColor c);
	void setModeMatrix(vector<int> modeMatrix);
	void setColor();
	void setBaseHue(int baseTone);
	ofColor getColor();
	
};

