#pragma once
#include "ofMain.h";
#include "Tone.h";
#include "SmallButton.h";

class PolygonColorControl
{
	float x;
	float y;
	float w = 120;
	float h = 100;
	int baseHue;
	Tone tone;
	ofColor color;
	int area;
	vector<Tone>& tones;
	vector<int> modeMatrix;
	vector<string> romanNumbers = {"I", "II", "III", "IV", "V", "VI", "VII"};

	vector<SmallButton> shadesButtons;

	void updateShadeButtons();
	
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
	);

	void display();
	bool isOver();
	bool mousePressed();
	void setModeMatrix(vector<int> modeMatrix);
	void setColor();
	void setBaseHue(int baseTone);
	float getLuminance();
	ofColor getColor();
	
};

