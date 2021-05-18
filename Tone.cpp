#include "Tone.h"

ofColor Tone::getColor() {
	ofColor c;
	c.setHsb(hue, 255, luminance * 2.5);
	return c;
}

void Tone::increaseTone() {
	number = number == 6 ? 0 : number + 1;
}

void Tone::decreaseTone() {
	number = number == 0 ? 6 : number - 1;
}