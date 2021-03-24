#pragma once
#include "ofMain.h"
#include "PolyDetector.h"
#include <vector>

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

	Formorgel();
	std::vector<PolyLine> lines;
	std::vector<PolyLine> generatePattern();
};

