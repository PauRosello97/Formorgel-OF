#include "DragController.h"

DragController::DragController(float& v, float _x, float _y, float _w, float _h) : value(v){
	x = _x;
	y = _y;
	w = _w;
	h = _h;
}

void DragController::display() {
	update();
	ofSetColor(0);
	ofDrawBitmapString(ofToString(initialX), x, y + 10);

	if (pressed) {
		ofSetColor(100, 155, 0);
	}else{
		ofSetColor(0, 255, 0);
	}
	ofDrawRectangle(x, y, w, h);
}

void DragController::update() {
	if (pressed) {
		value = ofGetMouseX() - initialX;
	}
}

bool DragController::isOver() {
	return ofGetMouseX() > x&& ofGetMouseX() < x + w && ofGetMouseY() > y&& ofGetMouseY() < y + h;
}

void DragController::mousePressed() {
	if (isOver()) {
		pressed = true;
		initialX = ofGetMouseX();
	}
}

bool DragController::mouseReleased() {
	if (pressed) {
		pressed = false;
		return true;
	}
	return false;
}
