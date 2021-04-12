#include "Oscillator.h"




void Oscillator::display() {
	button.display();
	//angleInput.display();
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
	//angleInput.mousePressed();
}