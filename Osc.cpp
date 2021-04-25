#include "Osc.h"

void Osc::display() {
	// Inputs
	offsetInput.display();
	angleInput.display();
	lengthInput.display();

	// Lines
	ofSetColor(255, 0, 0);
	int d = 3;
	float radius = 50;
	for (int i = 0; i < d; i++) {
		float a = (radius + i * 360 / d - 90);

		float startX = x + 100 + radius * offset * cos(radians(a));
		float startY = y + 100 + radius * offset * sin(radians(a));

		float fix = 150;

		float endX = startX + radius * length * cos(radians(fix + a + angle));
		float endY = startY + radius * length * sin(radians(fix + a + angle));

		ofDrawLine(startX, startY, endX, endY);
	}

	// Square
	ofSetColor(25, 25, 25);
	ofDrawRectangle(x + 10, y + 10, h-20, h-20);

	ofSetColor(0, 0, 0);
	if (isOver()) {
		ofSetColor(255, 0, 0);
	}
	else {
		ofSetColor(255, 255, 255);
	}
	
	ofDrawRectangle(x, y, w, h);
}

bool Osc::isOver() {
	return ofGetMouseX() > x&& ofGetMouseX() < x + w && ofGetMouseY() > y&& ofGetMouseY() < y + h;
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

float Osc::radians(float degrees) {
	float pi = 3.14159265359;
	return degrees * pi / 180;
}