#pragma once
#include "Formorgel.h";
#include "PolyDetector.h";

class GeometricSynth
{
	Formorgel formorgelA;
	Formorgel formorgelB;
	Formorgel formorgelC;
	PolyDetector polyDetector;

public:
	GeometricSynth();

	std::vector<PolyPol> polygons;
	std::vector<PolyLine> lines;

	void generateLines(Formorgel fA, Formorgel fB, Formorgel fC, int iterations);
	void generateComposition(Formorgel fA, Formorgel fB, Formorgel fC, int iterations);
	void display();
	void displayLines();
	void applyColors(map<int, ofColor> assignations);
};

