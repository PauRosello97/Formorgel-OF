#include "GeometryPanel.h"

bool GeometryPanel::mousePressed() {
	if (oscA.mousePressed()) {
		return true;
	}
	else if (oscB.mousePressed()) {
		return true;
	}
	return false;	
}