#include "SmallButton.h"

SmallButton::SmallButton(float _x, float _y, float _size) {
    x = _x;
    y = _y;
    size = _size;
    color = ofColor(20);
};

SmallButton::SmallButton(float _x, float _y, float _size, ofColor _color) {
    x = _x;
    y = _y;
    size = _size;
    color = _color;
};

void SmallButton::display() {
    ofSetColor(color);
    ofDrawRectangle(x - size / 2, y - size / 2, size, size);
}

bool SmallButton::isOver() {
    return ofGetMouseX() > x - size / 2 && ofGetMouseX() < x + size / 2 && ofGetMouseY() > y - size / 2 && ofGetMouseY() < y + size / 2;
}

void SmallButton::setColor(ofColor _color) {
    color = _color;
}

ofColor SmallButton::getColor() {
    return color;
}