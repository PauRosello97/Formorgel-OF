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
	void generateFourthLevelPack(float x, float y, float d);
	float radians(float degrees);
	float radius = 150;
	float offsetKnob;
	float angleKnob;
	float lengthKnob;
	int id;

public:
	Formorgel();
	Formorgel(float offsetKnob, float angleKnob, float lengthKnob, int id);
	std::vector<PolyLine> lines;
	std::vector<PolyLine> generatePattern();
};

