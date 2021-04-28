#pragma once
#include "ofMain.h";
#include "PolyDetector.h";
#include "PolygonColorControl.h";

class ColorPanel
{
	float x = 10;
	float y = 50;
	float w = 400;

	vector<PolyPol> polygons;
	vector<ofColor> colors;
	vector<int> areas;
	vector<PolygonColorControl> polygonColorControls;
	
public:
	map<int, ofColor> assignations;

	ColorPanel() {};
	ColorPanel(vector<PolyPol> _polygons);

	void display();
	void update(vector<PolyPol> _polygons);
	void updateAssignations();
	void mousePressed();
};

