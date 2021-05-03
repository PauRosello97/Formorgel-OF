#pragma once
#include "ofMain.h";
#include "PolyDetector.h";
#include "PolygonColorControl.h";
#include "ModeSelector.h"
#include "Tone.h"

class ColorPanel
{
	float x = 10;
	float y = 50;
	float w = 400;
	float h = 690;

	vector<PolyPol> polygons;
	vector<int> areas;
	vector<Tone> tones;
	vector<PolygonColorControl> polygonColorControls;
	ModeSelector modeSelector = ModeSelector(x + 10, y + 10);
	int nMode = 0;

	void updateModeArray();
	
public:
	vector<vector<int>> modesMatrix = {
		{0, 2, 4, 6, 7, 9, 11}, // Lydian
		{0, 2, 4, 5, 7, 9, 11}, // Ionian
		{0, 2, 4, 5, 7, 9, 10}, // Mixolydian
		{0, 2, 3, 5, 7, 9, 10}, // Dorian
		{0, 2, 3, 5, 7, 8, 10}, // Aeolian
		{0, 1, 3, 5, 7, 8, 10}, // Phrygian
		{0, 1, 3, 5, 6, 8, 10}  // Locrian
	};

	map<int, ofColor> assignations;

	ColorPanel() {};
	ColorPanel(vector<PolyPol> _polygons);

	void display();
	void update(vector<PolyPol> _polygons);
	void updateAssignations();
	void mousePressed();
};

