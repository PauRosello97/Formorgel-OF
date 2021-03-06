#include "Formorgel.h"

Formorgel::Formorgel(){}

Formorgel::Formorgel(float _offsetKnob, float _angleKnob, float _lengthKnob, int _id) {
	offsetKnob = _offsetKnob;
	angleKnob = _angleKnob;
	lengthKnob = _lengthKnob;
	id = _id;
}

std::vector<ofxPolyLine> Formorgel::generatePattern(int iterations) {
	lines = {};

	if (iterations == 0) {
		generateOneShape(ofGetWindowWidth() / 1.6, ofGetWindowHeight() / 2, 3, 0);
	}
	else if (iterations == 1) {
		generateOnePack(ofGetWindowWidth() / 1.6, ofGetWindowHeight() / 2, 3);
	}
	else if (iterations == 2) {
		generateSecondLevelPack(ofGetWindowWidth() / 1.6, ofGetWindowHeight() / 2, 3);
	}
	else if (iterations == 3) {
		generateThirdLevelPack(ofGetWindowWidth() / 1.6, ofGetWindowHeight() / 2, 3);
	}
	else if (iterations == 4) {
		generateFourthLevelPack(ofGetWindowWidth() / 1.6, ofGetWindowHeight() / 2, 3);
	}
	
	return lines;
}

void Formorgel::generateOneShape(float x, float y, float d, float r) {
	
	for (int i = 0; i < d; i++) {
		float angle = (r + i * 360 / d - 90);

		float fix = 150;

		float startX = x + radius * offsetKnob * cos(radians(fix + angle));
		float startY = y + radius * offsetKnob * sin(radians(fix + angle));

		float endX = startX + radius * lengthKnob * cos(radians(fix + angle + angleKnob));
		float endY = startY + radius * lengthKnob * sin(radians(fix + angle + angleKnob));
	
		lines.push_back({{ startX, startY }, { endX, endY }});
	}
}

void Formorgel::generateOnePack(float x, float y, float d) {
	float polygonVertexAngle = (180 * (d - 2) / d);
	float rep = 360 / polygonVertexAngle;
	float rotationRadius = radius;

	float extraR = d == 4 ? 45 : 90;

	//for (int i = 0; i < rep; i++) {
	for (int i = 0; i < 6; i++) {
		float angle = i * polygonVertexAngle + 90;
		generateOneShape(x + rotationRadius * cos(radians(angle + extraR)), y + rotationRadius * sin(radians(angle + extraR)), d, angle);
	}
}

void Formorgel::generateSecondLevelPack(float x, float y, float d) {
	float rotationRadius = 2 * radius * sin(radians(180 - 360 / d));
	int rep = int(pow(2 * sin(radians(180 - 360 / d)), 2));
	float extraR = d == 4 ? 45 : 0;

	for (int i = 0; i < rep; i++) {
		float angle = radians(extraR + i * 360 / rep);
		generateOnePack(x + rotationRadius * sin(angle), y + rotationRadius * cos(angle), d);
	}
}

void Formorgel::generateThirdLevelPack(float x, float y, float d) {
	int rep = int(pow(2 * sin(radians(180 - 360 / d)), 2));
	float rotationRadius = 2 * rep * radius / 2;
	float extraR = d == 4 ? 45 : 0;

	for (int i = 0; i < rep; i++) {
		float angle = radians(extraR + i * 360 / rep);
		generateSecondLevelPack(x - rotationRadius * cos(angle), y - rotationRadius * sin(angle), d);
	}
}

void Formorgel::generateFourthLevelPack(float x, float y, float d) {
	int rep = int(pow(2 * sin(radians(180 - 360 / d)), 2));
	float rotationRadius = 2 * rep * radius * sin(radians(180 - 360 / d));
	float extraR = d == 4 ? 45 : 0;

	for (int i = 0; i < rep; i++) {
		float angle = radians(extraR + i * 360 / rep);
		generateThirdLevelPack(x + rotationRadius * sin(angle), y + rotationRadius * cos(angle), d);
	}
}

float Formorgel::radians(float degrees) {
	float pi = 3.14159265359;
	return degrees * pi / 180;
}