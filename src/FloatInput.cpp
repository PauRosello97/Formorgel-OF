#include "FloatInput.h"

bool FloatInput::isOver() {
	return ofGetMouseX() > x && ofGetMouseX() < x + w && ofGetMouseY() > y && ofGetMouseY() < y + h;
}

void FloatInput::display() {
    update();
    dragController.display();
    ofSetColor(0);
    ofDrawBitmapString(label, x, y + 10);
    if (isOver()) {
        ofSetColor(120, 120, 120);
    }
    else {
        ofSetColor(200, 200, 200);
    }
    
    ofDrawRectangle(x, y, w, h);
}

void FloatInput::update() {
    if (dragController.isPressed()) {

    }
}

bool FloatInput::mousePressed() {
    if (isOver()) {
        dragController.mousePressed();
        return true;
    }
    return false;
}

bool FloatInput::mouseReleased() {
    return dragController.mouseReleased();
}

