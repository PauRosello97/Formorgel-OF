#include "Formorgel.h"

Formorgel::Formorgel(){}

Formorgel::Formorgel(float _offsetKnob, float _angleKnob, float _lengthKnob) {
	offsetKnob = _offsetKnob;
	angleKnob = _angleKnob;
	lengthKnob = _lengthKnob;

}

std::vector<PolyLine> Formorgel::generatePattern() {
	lines = {};

	//generateFourthLevelPack(ofGetWindowWidth() / 2 + x, ofGetWindowHeight() / 2 + y, 3);
	generateThirdLevelPack(ofGetWindowWidth()/2, ofGetWindowHeight()/2, 3);
	//generateSecondLevelPack((ofGetWindowWidth() / 2)+50, (ofGetWindowHeight() / 2) + 50, 3);
	
	return lines;
}


void Formorgel::generateOneShape(float x, float y, float d, float r) {
	
	for (int i = 0; i < d; i++) {
		float angle = (r + i * 360 / d - 90);

		float startX = x + radius * offsetKnob * cos(radians(angle));
		float startY = y + radius * offsetKnob * sin(radians(angle));

		float fix = 150;

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