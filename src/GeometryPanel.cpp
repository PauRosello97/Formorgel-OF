#include "GeometryPanel.h"

void GeometryPanel::display() {
	oscA.display();
	oscB.display();
	oscC.display();
	randomizeButton.display("Randomize");

	//Stroke
	ofSetColor(40);
	ofDrawLine(x, y, x, y + h);
	ofDrawLine(x+w, y, x+w, y + h);
	ofDrawLine(x, y+h, x+w, y + h);

	//Background fill
	ofSetColor(135);
	ofDrawRectangle(x, y, w, h);
};

void GeometryPanel::randomize() {
	oscA.randomize();
	oscB.randomize();
	oscC.randomize();
}

bool GeometryPanel::mousePressed() {
	if (oscA.mousePressed() || oscB.mousePressed() || oscC.mousePressed() || iterationsInput.mousePressed()) {
		return true;
	}
	else if (randomizeButton.mousePressed()) {
		randomize();
		return true;
	}
	return false;
}

bool GeometryPanel::mouseReleased() {
	if (oscA.mouseReleased() || oscB.mouseReleased() || oscC.mouseReleased() || iterationsInput.mouseReleased()) {
		return true;
	}
	return false;
}