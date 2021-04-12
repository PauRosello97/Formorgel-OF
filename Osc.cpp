#include "Osc.h"

void Osc::display() {
	//button.display();
	floatInput.display(x+10, y+10);
	//ofDrawBitmapString("Offset: " + ofToString(offset), x+100, y+100);
	//ofDrawBitmapString("Length: " + ofToString(length), x+100, y+120);
	ofSetColor(0, 0, 0);
	ofDrawBitmapString("AngleOSC: " + ofToString(value), x + 10, y + 140);
	if (isOver()) {
		ofSetColor(255, 0, 0);
	}
	else {
		ofSetColor(255, 255, 255);
	}
	
	ofDrawRectangle(x, y, w, h);
}

bool Osc::isOver() {
	return ofGetMouseX() > x&& ofGetMouseX() < x + w && ofGetMouseY() > y&& ofGetMouseY() < y + h;
}