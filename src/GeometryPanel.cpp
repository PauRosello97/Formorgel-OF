#include "GeometryPanel.h"

void GeometryPanel::display() {
	oscA.display();
	oscB.display();
	oscC.display();
	randomizeButton.display("Randomize");

	//Background fill
	ofSetColor(135);
	ofDrawRectangle(x, y, w, h);
	//Background stroke
	ofNoFill();
	ofSetColor(80);
	ofSetLineWidth(4);
	ofDrawRectangle(x, y, w, h); 
	ofFill();
	ofSetLineWidth(1);
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