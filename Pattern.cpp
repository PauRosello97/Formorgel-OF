#include "Pattern.h"

Pattern::Pattern() {
	
}

void Pattern::setup(ofShader _shader) {

	shader = _shader;
	doShader = true;

	generateLines();
	findIntersections();
	generateTriangles();
}

void Pattern::draw() {
	if (doShader) {
		shader.begin();

		// set thickness of ribbons
		shader.setUniform1f("thickness", 20);
	}

	for (Triangle triangle : triangles) { triangle.draw(); }
	ofSetColor(ofColor(255));
	for (Line line : lines) { line.draw(); }
	for (Node intersection : intersections) { intersection.draw(); }
	

	if (doShader) shader.end();

}

void Pattern::setDoShader(bool _doShader) {
	doShader = _doShader;
}

void Pattern::generateLines() {

	float w = ofGetWidth();
	float h = ofGetHeight();

	points.clear();
	for (int i = 0; i < 50; i++) {
		ofVec2f newPoint(ofRandom(0, w), ofRandom(0, h));
		points.push_back(newPoint);
	}

	lines.clear();
	for (int i = 0; i < 5; i++) {
		Line newLine(points[i], points[i+1], i);
		lines.push_back(newLine);
	}
}

void Pattern::findIntersections() {
	
	intersections.clear();
	//Afegim totes les interseccions a l'array.
	for (int i = 0; i < lines.size(); i++) {
		for (int j = i + 1; j < lines.size(); j++) {
			if (! lines[i].intersectsAt(lines[j]).getIsNull()) {
				Node intersection = lines[i].intersectsAt(lines[j]);
				vector<Line> intersectionLines = { lines[i], lines[j] };
				intersections.push_back(intersection);
			}
		}
	}

	/*
	// Unim interseccions iguals.
	for (int i = 0; i < intersections.size(); i++) {
		for (int j = 0; j < intersections.size(); j++) {
			if (i != j && sonElMateix(intersections.get(i), intersections.get(j))) {
				intersections.get(j).uneix(intersections.get(i));
				intersections.remove(i);
				i = i == 0 ? 0 : i - 1;
			}
		}
	}*/
}

void Pattern::generateTriangles() {
	Triangulator triangulator;
	if (intersections.size() != 0) {
		triangles = triangulator.triangulate(intersections);
	}
}

int Pattern::getNLines() {
	return lines.size();
}

int Pattern::getNNodes() {
	return intersections.size();
}

int Pattern::getNTriangles() {
	return triangles.size();
}