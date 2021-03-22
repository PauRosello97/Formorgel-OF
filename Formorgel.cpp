#include "Formorgel.h"

void Formorgel::generatePattern() {
	lines = {};

	generateSecondLevelPack(ofGetWindowWidth()/2, ofGetWindowHeight()/2, 3);
	//generateThirdLevelPack(ofGetWindowWidth() / 2, ofGetWindowHeight() / 2, 3);

	/*
	for (int i = 0; i < 50; i++) {
		lines.push_back({
			{ofRandom(ofGetWidth()),ofRandom(ofGetHeight())},
			{ofRandom(ofGetWidth()),ofRandom(ofGetHeight())}
			}
		);
	}
	*/

	PolyDetector pd;

	for (auto& l : lines)
	{
		pd.AddLine(l);
	}

	if (!pd.DetectPolygons())
	{
		logoutf("%s", "WARN: cannot detect polys!");
	}

	polygons = pd.polys;
}

void Formorgel::display() {
	for (int i = 0; i < lines.size(); i++) {
		ofSetColor(0, 0, 0);
		ofDrawLine(lines.at(i).a.x, lines.at(i).a.y, lines.at(i).b.x, lines.at(i).b.y);
	}
	for (int i = 0; i < polygons.size(); i++) {
		polygons.at(i).draw();
	}
}

void Formorgel::generateOneShape(float x, float y, float d, float r) {
	
	for (int i = 0; i < d; i++) {
		float angle = (r + i * 360 / d - 90);

		float startX = x + radius * offsetKnob * cos(radians(angle));
		float startY = y + radius * offsetKnob * sin(radians(angle));

		float fix = 150;

		float endX = startX + radius * lengthKnob * cos(radians(fix + angle + angleKnob));
		float endY = startY + radius * lengthKnob * sin(radians(fix + angle + angleKnob));
	
		std::cout << "------" << startX << "," << startY << "-" << endX << "," << endY << "\n";
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

float Formorgel::radians(float degrees) {
	float pi = 3.14159265359;
	return degrees * pi / 180;
}