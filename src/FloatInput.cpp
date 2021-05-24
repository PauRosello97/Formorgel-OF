#include "FloatInput.h"

void FloatInput::display() {
    // Stroke
    ofSetColor(40);
    ofDrawLine(x, y, x + w, y);
    ofDrawLine(x, y+h, x + w, y+h);
    ofDrawLine(x, y, x, y + h);
    ofDrawLine(x+w, y, x+w, y + h);

    // Controllers
    dragController.display();
    ofSetColor(40);
    ofRectangle rect = openSans.getStringBoundingBox(label, 0, 0);
    openSans.drawStringAsShapes(label, x + w / 2 - rect.width / 2, y+20);
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

