#include "Oscillators.h"

void Oscillators::mousePressed() {
	if (!oscA.mousePressed()) {
		oscB.mousePressed();
	}
}