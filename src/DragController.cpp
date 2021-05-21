#include "DragController.h"

DragController::DragController(float& v, float _x, float _y, float _w, float _h, float _step, float _min, float _max) : value(v){
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	step = _step;
	min = _min;
	max = _max;
	initialValue = v;
	sensibility = (max - min) / 200;
}

void DragController::display() {
	update();
	ofSetColor(0);
	ofDrawBitmapString(ofToString(value), x, y + 10);

	ofFill();
	if (pressed) {
		ofSetColor(100, 155, 0);
	}
	else {
		ofSetColor(0, 255, 0);
	}
	ofDrawRectangle(x, y, w, h);
	ofNoFill();
	ofSetColor(0); // contour (stroke) color  
	ofDrawRectangle(x, y, w, h);
	ofFill();
}

void DragController::update() {
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

bool DragController::isOver() {
	return ofGetMouseX() > x&& ofGetMouseX() < x + w && ofGetMouseY() > y&& ofGetMouseY() < y + h;
}

void DragController::mousePressed() {
	if (isOver()) {
		pressed = true;
		initialX = ofGetMouseX();
		initialValue = value;
	}
}

bool DragController::mouseReleased() {
	if (pressed) {
		pressed = false;
		return true;
	}
	return false;
}
