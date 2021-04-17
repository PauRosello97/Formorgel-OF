#include "Oscillators.h"

bool Oscillators::mousePressed() {
	if (oscA.mousePressed()) {
		return true;
	}
	else if (oscB.mousePressed()) {
		return true;
	}
	return false;	
}