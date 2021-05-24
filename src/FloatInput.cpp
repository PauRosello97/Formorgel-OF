#include "FloatInput.h"

bool FloatInput::isOver() {
	return ofGetMouseX() > x && ofGetMouseX() < x + w && ofGetMouseY() > y && ofGetMouseY() < y + h;
}

void FloatInput::display() {
    dragController.display();
    ofSetColor(0);
    ofDrawBitmapString(label, x+10, y + 15);

    ofSetColor(165);
    ofDrawRectangle(x, y, w, h);
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

