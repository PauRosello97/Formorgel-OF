#include "Osc.h"

void Osc::display() {
	//Stroke
	ofSetColor(40);
	ofDrawLine(x+10, y-5, x+w-10, y-5);

	// Inputs
	offsetInput.display();
	angleInput.display();
	lengthInput.display();

	// Lines
	ofSetColor(165);
	int d = 3;
	float radius = 50;
	for (int i = 0; i < d; i++) {
		float a = (radius +10 + i * 360 / d );

		float fix = 150;

		float startX = x + 110 + radius * offset * cos(radians(fix + a));
		float startY = y + 110 + radius * offset * sin(radians(fix + a));

		float endX = startX + radius * length * cos(radians(fix + a + angle));
		float endY = startY + radius * length * sin(radians(fix + a + angle));

		ofDrawLine(startX, startY, endX, endY);
	}

	// Square
	ofSetColor(40);
	ofDrawRectangle(x + 10, y + 10, h-20, h-20);
}

float Osc::radians(float degrees) {
	float pi = 3.14159265359;
	return degrees * pi / 180;
}

void Osc::randomize() {
	offset = round(ofRandom(100)) / 100;
	angle = round(ofRandom(90));
	length = round(50 + ofRandom(100)) / 100;
}

bool Osc::mousePressed() {
	if (isOver()) {
		if (!offsetInput.mousePressed()) {
			if (!angleInput.mousePressed()) {
				lengthInput.mousePressed();
			}
		}
		return true;
	}
	else {
		return false;
	}
}

bool Osc::mouseReleased() {
	if (offsetInput.mouseReleased() || lengthInput.mouseReleased() || angleInput.mouseReleased()) {
		return true;
	}
	return false;
}