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
}

void Knob::display() {
	update();

	// Text
	ofSetColor(0);
	ofDrawBitmapString(ofToString(value), x+20, y + 70);
	float pi = 3.14159265359;
	float proportion = pi/2 + (2 * pi * (value-min) / (max-min));

	// Knob
	float cx = x + w / 2;
	float cy = y + h * 0.4;
	float ex = cx + cos(proportion) * knobRadius;
	float ey = cy + sin(proportion) * knobRadius;

	ofSetLineWidth(3);
	ofSetColor(0);
	ofDrawLine(cx, cy, ex, ey);
	ofSetLineWidth(1);

	ofSetColor(200, 255, 200);
	ofDrawCircle(cx, cy, knobRadius);

	// Fill
	ofFill();
	ofSetColor(135);

	ofDrawRectangle(x, y, w, h);

	// Stroke
	ofNoFill();
	ofSetColor(0);
	ofDrawRectangle(x, y, w, h);
	ofFill();
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
