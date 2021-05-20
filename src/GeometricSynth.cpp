#include "GeometricSynth.h"

GeometricSynth::GeometricSynth(){}

void GeometricSynth::generateComposition(Formorgel fA, Formorgel fB, Formorgel fC, int iterations) {
	generateLines(fA, fB, fC, iterations);
	
	polyDetector.detectPolygons(lines);

	polygons = polyDetector.polys;
}

void GeometricSynth::generateLines(Formorgel fA, Formorgel fB, Formorgel fC, int iterations) {
	formorgelA = fA;
	formorgelB = fB;
	formorgelC = fC;

	lines = formorgelA.generatePattern(iterations);
	vector<ofxPolyLine> linesB = formorgelB.generatePattern(iterations);
	vector<ofxPolyLine> linesC = formorgelC.generatePattern(iterations);

	for (auto& l : linesB) { lines.push_back(l); }
	for (auto& l : linesC) { lines.push_back(l); }
}

void GeometricSynth::display() {
	for (int i = 0; i < polygons.size(); i++) {
		polygons.at(i).draw();
	}
}

void GeometricSynth::displayLines() {
	ofSetColor(0);
	for (int i = 0; i < lines.size(); i++) {
		ofDrawLine(lines.at(i).a.x, lines.at(i).a.y, lines.at(i).b.x, lines.at(i).b.y);
	}	
}

void GeometricSynth::applyColors(map<int, ofColor> assignations) {
	map<int, ofColor>::iterator itr;

	for (int i = 0; i < polygons.size(); i++) {
		polygons.at(i).setColor(assignations[polygons.at(i).roundArea()]);
	}
}