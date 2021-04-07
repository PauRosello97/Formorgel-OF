#pragma once
#include "Formorgel.h";
#include "PolyDetector.h";

class GeometricSynth
{
	Formorgel formorgelA;
	Formorgel formorgelB;
	PolyDetector polyDetector;

public:
	GeometricSynth();

	std::vector<PolyPol> polygons;
	std::vector<PolyLine> lines;

	void generateComposition(Formorgel fA, Formorgel fB);
	void display();
};

