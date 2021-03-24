#include "GeometricSynth.h"

void GeometricSynth::generateComposition() {
	lines = formorgel.generatePattern();

	for (auto& l : lines)
	{
		polyDetector.AddLine(l);
	}

	polyDetector.DetectPolygons();

	polygons = polyDetector.polys;

}
void GeometricSynth::display() {

	for (int i = 0; i < lines.size(); i++) {
		ofSetColor(0, 0, 0);
		ofDrawLine(lines.at(i).a.x, lines.at(i).a.y, lines.at(i).b.x, lines.at(i).b.y);
	}

	for (int i = 0; i < polygons.size(); i++) {
		polygons.at(i).draw();
	}
}

