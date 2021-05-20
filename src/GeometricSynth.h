#pragma once
#include "Formorgel.h";
#include "ofxPolygonDetector.h";

class GeometricSynth
{
	Formorgel formorgelA;
	Formorgel formorgelB;
	Formorgel formorgelC;
	ofxPolygonDetector polyDetector;

public:
	GeometricSynth();

	std::vector<ofxPolyPol> polygons;
	std::vector<ofxPolyLine> lines;

	void generateLines(Formorgel fA, Formorgel fB, Formorgel fC, int iterations);
	void generateComposition(Formorgel fA, Formorgel fB, Formorgel fC, int iterations);
	void display();
	void displayLines();
	void applyColors(map<int, ofColor> assignations);
};

