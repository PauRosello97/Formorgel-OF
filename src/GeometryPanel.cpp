#include "GeometryPanel.h"

void GeometryPanel::display() {
	oscA.display();
	oscB.display();
	oscC.display();
	randomizeButton.display("Randomize");
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