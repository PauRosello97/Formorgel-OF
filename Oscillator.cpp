#include "Oscillator.h"

Oscillator::Oscillator(){}

Oscillator::Oscillator(float _x, float _y, float _w, float _h) {
	x = _x;
	y = _y;
	w = _w;
	h = _h;
	button = Button(x+2*w/3, y+h-30, w/3, 30);
	//angleInput = Input(angle, x+10, y+10);
}

void Oscillator::display() {
	button.display();
	angleInput.display();
	//ofDrawBitmapString("Offset: " + ofToString(offset), x+100, y+100);
	//ofDrawBitmapString("Length: " + ofToString(length), x+100, y+120);
	ofDrawBitmapString("Angle: " + ofToString(angle), x+100, y+140);
	ofSetColor(255, 255, 255);
	ofDrawRectangle(x, y, w, h);
}

bool Oscillator::isOverButton() {
	return button.isOver();
}

void Oscillator::mousePressed() {
	angleInput.mousePressed();
}