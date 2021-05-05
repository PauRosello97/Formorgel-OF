#include "PolygonColorControl.h"

PolygonColorControl::PolygonColorControl(
	float _x,
	float _y,
	int _area,
	Tone _tone,
	vector<Tone>& _tones,
	vector<int> _modeMatrix,
	int baseTone
) : tones(_tones) {
	modeMatrix = _modeMatrix;
	x = _x;
	y = _y;
	area = _area;
	displayingDialog = false;
	tone = _tone;
	baseHue = baseTone * 30;
	setColor();

	float shadeSize = w / 7;
	for (int i = 0; i < 7; i++) {
		ofColor buttonColor;
		buttonColor.setHsb(color.getHue(), 100, i * 255 / 6);
		shadesButtons.push_back(
			SmallButton(
				x + shadeSize*i + shadeSize / 2 , 
				y + h - shadeSize / 2, 
				shadeSize,
				buttonColor
			)
		);
	}
};

void PolygonColorControl::updateShadeButtons() {
	for (int i = 0; i < shadesButtons.size(); i++) {
		ofColor buttonColor;
		buttonColor.setHsb(color.getHue(), 100, i * 255 / 6);
		shadesButtons[i].setColor(buttonColor);
	}
}

void PolygonColorControl::display() {
	// Text
	if (tone.luminance > 90) {
		ofSetColor(0);
	}
	else {
		ofSetColor(255);
	}
	ofDrawBitmapString(romanNumbers[tone.number] + " (" + ofToString(modeMatrix[tone.number]) + ")", x + 10, y + 20);
	ofDrawBitmapString("(" + ofToString(round(360*color.getHue()/255)) + ", " + ofToString(round(tone.luminance)) + ")", x + 10, y + 40);
	
	// Shades
	for (SmallButton shade : shadesButtons) {
		shade.display();
	}
	
	// Background
	ofSetColor(color);
	ofDrawRectangle(x, y, w, h);
}

bool PolygonColorControl::isOver() {
	return ofGetMouseX() > x&& ofGetMouseX() < x + w && ofGetMouseY() > y && ofGetMouseY() < y + h;
}

bool PolygonColorControl::mousePressed() {
	if (isOver()) {
		for (SmallButton shade : shadesButtons) {
			if (shade.isOver()) {
				//setColor(ofColor(255, 0, 0));
				tone.luminance = 100 * shade.getColor().getBrightness() / 255;
				//tone.luminance = 255;				
				break;
			}
		}
		return true;
	}
	return false;
}

void PolygonColorControl::setModeMatrix(vector<int> _modeMatrix) {
	modeMatrix = _modeMatrix;
}

void PolygonColorControl::setColor() {
	color.setHsb(((baseHue + modeMatrix[tone.number] * 30) % 360) * 0.7083, 255, tone.luminance*2.5);
	updateShadeButtons();
}

ofColor PolygonColorControl::getColor() {
	return color;
}

void PolygonColorControl::setBaseHue(int baseTone) {
	baseHue = baseTone * 30;
}

float PolygonColorControl::getLuminance() {
	return tone.luminance;
}