#pragma once
#include "ofMain.h";
#include "ofxPolygonDetector.h";
#include "PolygonColorControl.h";
#include "Selector.h";
#include "Tone.h";
#include "Button.h";

class ColorPanel
{
	float x = 10;
	float y = 50;
	float w = 400;
	float h = 690;

	int baseTone = 0;
	vector<PolyPol> polygons;
	vector<int> areas;
	vector<Tone> tones;
	vector<PolygonColorControl> polygonColorControls;
	Selector modeSelector = Selector(
		x + 10, 
		y + 10, 
		{ "Lydian", "Ionian", "Mixolydian", "Dorian", "Aeolian", "Phrygian", "Locrian" }
	);
	Selector baseToneSelector = Selector(
		x + 10, 
		y + 70, 
		{ "0 Red", "30 Orange", "60 Yellow", "90 Yellow-Green", "120 Green", "150 Green-Cyan", "180 Cyan", "210 Cyan-Blue", "240 Blue", "270 Blue-Magenta", "300 Magenta", "330 Red-Magenta" }
	);
	int nMode = 0;

	void updateControls();
	
public:
	vector<vector<int>> modesMatrix = {
		{0, 2, 4, 6, 1, 3, 5}, // Lydian
		{0, 2, 4, 11, 1, 3, 5}, // Ionian
		{0, 2, 4, 11, 1, 3, 10}, // Mixolydian
		{0, 2, 9, 11, 1, 3, 10}, // Dorian
		{0, 2, 9, 11, 1, 8, 10}, // Aeolian
		{0, 7, 9, 11, 1, 8, 10}, // Phrygian
		{0, 7, 9, 11, 6, 8, 10}  // Locrian
	};

	map<int, ofColor> assignations;

	ColorPanel() {};
	ColorPanel(vector<PolyPol> _polygons);

	void display();
	void update(vector<PolyPol> _polygons);
	void updateAssignations();
	void mousePressed();
};

