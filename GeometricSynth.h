#pragma once
#include "Formorgel.h";
#include "PolyDetector.h";

class GeometricSynth
{
public:
	GeometricSynth();
	Formorgel formorgelA;
	Formorgel formorgelB;
	PolyDetector polyDetector;

	std::vector<PolyPol> polygons;
	std::vector<PolyLine> lines;

	void generateComposition();
	void display();

	
};

