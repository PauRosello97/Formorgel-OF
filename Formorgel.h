#pragma once
#include <vector>
#include "PolyDetector.h"

class Formorgel
{
	void generateOneShape(float x, float y, float d, float r);
	void generateOnePack(float x, float y, float d);
	void generateSecondLevelPack(float x, float y, float d);
	void generateThirdLevelPack(float x, float y, float d);
	float radians(float degrees);
	float radius = 100;
	float offsetKnob = 0;
	float angleKnob = 0;
	float lengthKnob = 2;

public:

	std::vector<PolyPol> polygons;
	std::vector<PolyLine> lines;

	void generatePattern();
	void display();
	
};

