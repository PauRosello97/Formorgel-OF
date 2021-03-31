#include "GeometricSynth.h"

GeometricSynth::GeometricSynth(){}

void GeometricSynth::generateComposition() {
	formorgelA = Formorgel(0, 0, 2);
	formorgelB = Formorgel(0.6, 0, 0.5);

	lines = formorgelA.generatePattern();
	std::vector<PolyLine> linesB = formorgelB.generatePattern();
	
	for (auto& l : linesB) { lines.push_back(l); }
	for (auto& l : lines){ polyDetector.AddLine(l); }

	polyDetector.DetectPolygons();

	polygons = polyDetector.polys;

}
void GeometricSynth::display() {
	/*
	ofSetColor(0, 0, 0);
	for (int i = 0; i < lines.size(); i++) {
		ofDrawLine(lines.at(i).a.x, lines.at(i).a.y, lines.at(i).b.x, lines.at(i).b.y);
	}
	*/

	
	for (int i = 0; i < polygons.size(); i++) {
		polygons.at(i).draw();
	}
		
}

