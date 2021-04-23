#include "FloatInput.h"

bool FloatInput::isOver() {
	return ofGetMouseX() > x && ofGetMouseX() < x + w && ofGetMouseY() > y && ofGetMouseY() < y + h;
}

void FloatInput::display() {
    plusButton.display();
    lessButton.display();
    ofSetColor(0, 0, 0);
    ofDrawBitmapString(label + ": " + ofToString(value), x + 10, y + 20);
    if (isOver()) {
        ofSetColor(120, 120, 120);
    }
    else {
        ofSetColor(200, 200, 200);
    }
    
    ofDrawRectangle(x, y, w, h);
}

bool FloatInput::mousePressed() {
    if (isOver()) {
        modifyValue();
        return true;
    }
    return false;
}
