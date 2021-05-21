#include "FloatInput.h"

bool FloatInput::isOver() {
	return ofGetMouseX() > x && ofGetMouseX() < x + w && ofGetMouseY() > y && ofGetMouseY() < y + h;
}

void FloatInput::display() {
    //plusButton.display();
    //lessButton.display();
    update();
    dragController.display();
    ofSetColor(0);
    ofDrawBitmapString(label + ": " + ofToString(value), x, y + 10);
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
    dragController.mousePressed();
    if (isOver()) {
        modifyValue();
        return true;
    }
    return false;
}

bool FloatInput::mouseReleased() {
    return dragController.mouseReleased();
}

void FloatInput::modifyValue() {
    /*
    if (plusButton.isOver()) {
        value += step;
        if (value > max) {
            value = max;
        }
    }
    else if (lessButton.isOver()) {
        value -= step;
        if (value < min) {
            value = min;
        }
    }
    */
}
