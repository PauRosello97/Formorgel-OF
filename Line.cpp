#include "Line.h"


Line::Line(ofVec2f _start, ofVec2f _end, int _id) {
	start = _start;
	end = _end;
	id = _id;
	m = ((start.y - end.y) / (start.x - end.x));
	n = (start.y - m * start.x);
}

void Line::draw() {
	ofDrawLine(start, end);
}

Node Line::intersectsAt(Line other) {
	return lineIntersection(other);
}

Node Line::lineIntersection(Line other) {
    float x1 = start.x;
    float y1 = start.y;
    float x2 = end.x;
    float y2 = end.y;

    float x3 = other.start.x;
    float y3 = other.start.y;
    float x4 = other.end.x;
    float y4 = other.end.y;

    float bx = x2 - x1;
    float by = y2 - y1;
    float dx = x4 - x3;
    float dy = y4 - y3;

    float b_dot_d_perp = bx * dy - by * dx;

    if (b_dot_d_perp == 0) {
        return Node();
    }

    float cx = x3 - x1;
    float cy = y3 - y1;

    float t = (cx * dy - cy * dx) / b_dot_d_perp;
    if (t < 0 || t > 1) {
        return Node();
    }

    float u = (cx * by - cy * bx) / b_dot_d_perp;
    if (u < 0 || u > 1) {
        return Node();
    }

    return Node(x1 + t * bx, y1 + t * by);
}
