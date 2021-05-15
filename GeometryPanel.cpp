#include "GeometryPanel.h"

bool GeometryPanel::mousePressed() {
	if (oscA.mousePressed()) {
		return true;
	}
	else if (oscB.mousePressed()) {
		return true;
	}
	else if (oscC.mousePressed()) {
		return true;
	}
	else if (iterationsInput.mousePressed()) {
		return true;
	}
	return false;	
}