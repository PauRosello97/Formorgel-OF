#pragma once

#include "ofMain.h"
#include "../GeometricSynth.h";
#include "../GeometryPanel.h";
#include "../ColorPanel.h";
#include "../Button.h";
#include "../GeometryColorSwitch.h";

class ofApp : public ofBaseApp{

	GeometryPanel geometryPanel;
	ColorPanel colorPanel;
	Button applyButton;
	Button displayLinesToggle;
	Button displayPolygonsToggle;
	GeometryColorSwitch geometryColorSwitch;
	bool displayingLines = true;
	bool displayingPolygons = false;

	float lateralWidth;
	bool workingMode = true;

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);

	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	void newPattern();

	GeometricSynth geometricSynth;
};
