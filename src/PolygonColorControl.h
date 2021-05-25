#pragma once
#include "ofMain.h";
#include "Tone.h";
#include "SmallButton.h";
#include "Touchable.h";

class PolygonColorControl : public Touchable
{	
	int baseHue;
	
	ofColor color;
	int area;
	vector<Tone>& tones;
	vector<int> modeMatrix;
	vector<string> romanNumbers = {"I", "II", "III", "IV", "V", "VI", "VII"};

	ofxHLuv HLuv;

	vector<SmallButton> shadesButtons;
	ofTrueTypeFont openSans;

	void updateShadeButtons(); 
	
	void drawPreviousArrow(float ax, float ay);
	void drawNextArrow(float ax, float ay);
	bool isOverPrevious();
	bool isOverNext();
	
	bool isDark();

public:
	Tone tone;
	bool displayingDialog;
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
	bool mousePressed();
	void setModeMatrix(vector<int> modeMatrix);
	void setColor();
	void setBaseHue(int baseTone);
	float getLuminance();
	ofColor getColor();
	
};

