#pragma once

#include "ofMain.h"
#include "GeometricSynth.h"
#include "GeometryPanel.h"
#include "ColorPanel.h"
#include "Button.h"
#include "GeometryColorSwitch.h"
#include "FloatInput.h"
#include "InfoButton.h"
#include "InfoOverlay.h"

class ofApp : public ofBaseApp{
	
	GeometryPanel geometryPanel;
	ColorPanel colorPanel;
	Button applyButton;
	Button displayLinesToggle;
	Button displayPolygonsToggle;
	Button downloadButton;
	GeometryColorSwitch geometryColorSwitch;
	InfoButton infoButton;
	InfoOverlay infoOverlay;

	bool displayingLines = true;
	bool displayingPolygons = false;
	bool displayingOverlay = false;

	float lateralWidth;
	bool workingMode = true;
	int iterations = 0;

	ofImage screenshot;

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
