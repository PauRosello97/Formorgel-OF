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
	w = 114;
	h = 100;
	area = _area;
	displayingDialog = false;
	tone = _tone;
	baseHue = baseTone * 30;
	setColor();

	float shadeSize = w / 7;
	for (int i = 0; i < 7; i++) {
		ofColor buttonColor = HLuv.getColor(tone.hue, i * 100 / 6);		
		shadesButtons.push_back(
			SmallButton(
				x + shadeSize*i + shadeSize / 2 , 
				y + h - shadeSize / 2, 
				shadeSize,
				buttonColor
			)
		);
	}
	openSans.load("OpenSans/OpenSans-Regular.ttf", 12, false, false, true);
};

void PolygonColorControl::updateShadeButtons() {
	for (int i = 0; i < shadesButtons.size(); i++) {
		ofColor buttonColor = HLuv.getColor(tone.hue, i * 100 / 6);
		shadesButtons[i].setColor(buttonColor);
	}
}

void PolygonColorControl::display() {
	// Text
	if (isDark()) {
		ofSetColor(255);
	}
	else {
		ofSetColor(40);
	}
	string romanName = romanNumbers[tone.number];
	ofDrawBitmapString(romanName, x -romanName.length()*4 + w/2, y + h/2 );
	//ofRectangle rect = openSans.getStringBoundingBox(romanName, 0, 0);
	//openSans.drawStringAsShapes(romanName, x, y);

	// Arrows
	drawPreviousArrow(x + 10, y -5 + h / 2);
	drawNextArrow(x + w - 10, y -5 + h / 2);
	
	// Stroke
	ofSetColor(40);
	ofDrawLine(x, y, x + w, y);
	ofDrawLine(x, y + h, x + w, y + h);
	ofDrawLine(x, y, x, y + h);
	ofDrawLine(x+w, y, x+w, y + h);

	// Shades
	for (SmallButton shade : shadesButtons) {
		shade.display();
	}
	
	// Background
	ofSetColor(color);
	ofDrawRectangle(x, y, w, h);
}

bool PolygonColorControl::mousePressed() {
	
	if (isOver()) {
		for (int i = 0; i < shadesButtons.size(); i++) {
			if (shadesButtons[i].isOver()) {
				tone.luminance = i * 100 / 6;
				break;
			}
		}
		if (isOverNext()) {
			tone.increaseTone();
			tone.hue = baseHue + modeMatrix[tone.number] * 30;
			return true;
		}
		if (isOverPrevious()) {
			tone.decreaseTone();
			tone.hue = baseHue + modeMatrix[tone.number] * 30;
			return true;
		}
		return true;
	}
	return false;
}

void PolygonColorControl::setModeMatrix(vector<int> _modeMatrix) {
	modeMatrix = _modeMatrix;
}

void PolygonColorControl::setColor() {
	color = HLuv.getColor((baseHue + modeMatrix[tone.number] * 30) % 360, tone.luminance);
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

void PolygonColorControl::drawPreviousArrow(float ax, float ay) {
	ofPushStyle();
	if (isOverPrevious()) {
		ofSetLineWidth(2);
	}
	if (isDark()) {
		ofSetColor(255);
	}
	else {
		ofSetColor(40);
	}
	ofDrawLine(ax, ay, ax + 7, ay - 7);
	ofDrawLine(ax, ay, ax + 7, ay + 7);
	ofPopStyle();
}

void PolygonColorControl::drawNextArrow(float ax, float ay) {
	ofPushStyle();
	if (isOverNext()) {
		ofSetLineWidth(2);
	}
	if (isDark()) {
		ofSetColor(255);
	}
	else {
		ofSetColor(40);		
	}
	ofDrawLine(ax, ay, ax - 7, ay - 7);
	ofDrawLine(ax, ay, ax - 7, ay + 7);
	ofPopStyle();
}

bool PolygonColorControl::isOverPrevious() {
	return (ofGetMouseX() > x&& ofGetMouseX() < x + w / 2 && ofGetMouseY() > y && ofGetMouseY() < y + h -w/7);
}

bool PolygonColorControl::isOverNext() {
	return (ofGetMouseX() > x + w / 2 && ofGetMouseX() < x + w && ofGetMouseY() > y&& ofGetMouseY() < y + h-w/7);
}

bool PolygonColorControl::isDark() {
	if (tone.luminance > 70) {
		return false;
	}
	return true;
}