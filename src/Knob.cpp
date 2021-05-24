#include "Knob.h"

Knob::Knob(float& v, float _x, float _y, float _w, float _h, float _min, float _max) : value(v){
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	min = _min;
	max = _max;
	initialValue = v;
	sensibility = (max - min) / 200;

	openSans.load("OpenSans/OpenSans-Regular.ttf", 12, false, false, true);
}

void Knob::display() {
	update();

	// Text
	ofSetColor(40);
	ofRectangle rect = openSans.getStringBoundingBox(ofToString(value), 0, 0);
	openSans.drawStringAsShapes(ofToString(value), x + w/2 - rect.width/2, y + 70);
	float pi = 3.14159265359;
	float proportion = pi/2 + (2 * pi * (value-min) / (max-min));

	// Knob
	float cx = x + w / 2;
	float cy = y + h * 0.4;
	float ex = cx + cos(proportion) * knobRadius;
	float ey = cy + sin(proportion) * knobRadius;

	if (pressed) {
		ofSetColor(165);
	}
	else {
		ofSetColor(40);
	}

	ofSetLineWidth(3);
	ofDrawLine(cx, cy, ex, ey); // Line
	ofSetLineWidth(1);

	ofNoFill();
	ofSetLineWidth(4);
	ofDrawCircle(cx, cy, knobRadius); // Circle
	ofFill();
	ofSetLineWidth(1);
}

void Knob::update() {
	if (pressed) {
		value = initialValue + (ofGetMouseX() - initialX) * sensibility;
		if (value > max) {
			value = max;
		}
		else if (value < min) {
			value = min;
		}
	}
}

bool Knob::isOver() {
	return ofGetMouseX() > x&& ofGetMouseX() < x + w && ofGetMouseY() > y&& ofGetMouseY() < y + h;
}

void Knob::mousePressed() {
	if (isOver()) {
		pressed = true;
		initialX = ofGetMouseX();
		initialValue = value;
	}
}

bool Knob::mouseReleased() {
	if (pressed) {
		pressed = false;
		return true;
	}
	return false;
}