#include "Tone.h"

ofColor Tone::getColor() {
	return HLuv.getColor(hue, luminance);
}

void Tone::increaseTone() {
	number = number == 6 ? 0 : number + 1;
}

void Tone::decreaseTone() {
	number = number == 0 ? 6 : number - 1;
}